#include <iostream>
#include <fstream>
#include <memory>
#include <optional>
#include <array>
#include <string>
#include <string_view>
#include <vector>
#include <cctype>
#include <cstdlib>

constexpr size_t LIGTH_GRID_SIZE = 1000;
constexpr size_t INST_LINE_BUFFER_SIZE = 50;

enum class InstOp{
    TOOGLE,
    TURN_OFF,
    TURN_ON
};

struct Vector2d{
public:
    int32_t x;
    int32_t y;

public:
    friend std::ostream& operator<<(std::ostream& os, const Vector2d& val);
};
std::ostream& operator<<(std::ostream& os, const Vector2d& val){
    os << val.x << "," << val.y;
    return os;
}

struct Range{
public:
    Vector2d start;
    Vector2d end;
public:
    Range(Vector2d start, Vector2d end)
    : start{start}, end{end}
    {}

    friend std::ostream& operator<<(std::ostream& os, const Range& val);
};
std::ostream& operator<<(std::ostream& os, const Range& val){
    os << val.start << " through " << val.end;
    return os;
}

class Inst{
private:
    InstOp m_op;
    Range m_selection;
public:
    Inst(InstOp op, Range selection) :
        m_op{op},
        m_selection{selection}
    {}

    static std::optional<Inst> get_next_inst_from_stream(std::ifstream& stream){
        if (stream.eof()){
            return {};
        }

        std::array<char, INST_LINE_BUFFER_SIZE> lbuffer;
        stream.getline(lbuffer.data(), lbuffer.max_size());

        std::string_view line{lbuffer.data()};
        if (line.empty()){
            return {};
        }

        InstOp op;
        std::string_view next_part = extract_operation_from_line(line, op);
        next_part.remove_prefix(1); //remove trailing white space        
        Range selection = extract_range_from_line(next_part);
        return Inst{op, selection};
    }

    friend std::ostream& operator<<(std::ostream& os, const Inst& val);

    void apply_to(std::array<bool, LIGTH_GRID_SIZE * LIGTH_GRID_SIZE>& grid){
        int32_t sr = m_selection.start.y;
        int32_t sc = m_selection.start.x;
        int32_t er = m_selection.end.y;
        int32_t ec = m_selection.end.x;
        for (size_t i=sr; i <= er; ++i){
            for (size_t j=sc; j<= ec; ++j){
                bool* cit = grid.data() + ((i*LIGTH_GRID_SIZE) + j);
                switch(m_op){
                    case InstOp::TURN_OFF:
                        *cit = false;
                        break;
                    case InstOp::TURN_ON:
                        *cit = true;
                        break;
                    case InstOp::TOOGLE:
                        *cit = !(*cit);
                        break;
                }
            }
        }
    }

    void apply_to(std::vector<int32_t>& grid){
        int8_t operand;
        switch(m_op){
            case InstOp::TURN_OFF:
                operand = -1;
                break;
            case InstOp::TURN_ON:
                operand = 1;
                break;
            case InstOp::TOOGLE:
                operand = 2;
                break;
        }

        int32_t sr = m_selection.start.y;
        int32_t sc = m_selection.start.x;
        int32_t er = m_selection.end.y;
        int32_t ec = m_selection.end.x;
        for (size_t i=sr; i <= er; ++i){
            for (size_t j=sc; j <= ec; ++j){
                int32_t* cit = grid.data() + ((i*LIGTH_GRID_SIZE) + j);
                *cit += operand;
                if (*cit < 0){
                    *cit = 0;
                }
            }
        }
    }

private:
    static std::string_view extract_operation_from_line(const std::string_view line, InstOp& op){
        constexpr std::string_view toogle{"toggle"};
        constexpr std::string_view turn_on{"turn on"};
        constexpr std::string_view turn_off{"turn off"};

        auto lb = line.begin();
        auto le = line.end();
        if (line.starts_with(toogle)){
            op = InstOp::TOOGLE;
            return {lb + toogle.size(), le};
        } else if (line.starts_with(turn_on)){
            op = InstOp::TURN_ON;
            return {lb + turn_on.size(), le};
        } else {
            op = InstOp::TURN_OFF;
            return {lb + turn_off.size(), le};
        }
    }

    static std::string_view extract_number_from_line(const std::string_view line, int32_t& out){
        std::array<char, 6> nbuf;
        size_t i;
        for (i=0; i < 6; ++i){
            char c = line[i];
            if (!std::isdigit(c)){
                nbuf[i] = '\0';
                break;
            }else{
                nbuf[i] = c;
            }
        }
        out = std::atoi(nbuf.data());
        return line.substr(i);
    }

    static std::string_view extract_vect2d_from_line(const std::string_view line, Vector2d& out){
        std::string_view next_part = extract_number_from_line(line, out.x);
        next_part.remove_prefix(1); //remove comma separator
        return extract_number_from_line(next_part, out.y);
    }

    static Range extract_range_from_line(const std::string_view line){
        constexpr std::string_view through{" through "};

        Vector2d start, end;
        std::string_view next_part = extract_vect2d_from_line(line, start);
        next_part.remove_prefix(through.size());
        extract_vect2d_from_line(next_part, end);
        return {start, end};
    }
};
std::ostream& operator<<(std::ostream& os, const Inst& val){
    switch(val.m_op){
        case InstOp::TOOGLE:
            os << "toggle";
            break;
        case InstOp::TURN_OFF:
            os << "turn off";
            break;
        case InstOp::TURN_ON:
            os << "turn on";
            break;
    }

    os << " " << val.m_selection;
    return os;
}

size_t count_ligths(std::array<bool, LIGTH_GRID_SIZE * LIGTH_GRID_SIZE>& grid){
    size_t c = 0;
    for(auto ligth : grid){
        if(ligth){
            c++;
        }
    }
    return c;
}

size_t sum_ligths(std::vector<int32_t>& grid){
    size_t sum = 0;
    for (auto ligth : grid){
        sum += ligth;
    }
    return sum;
}

int main(){
    std::ifstream input{"input.txt"};
    std::array<bool, LIGTH_GRID_SIZE * LIGTH_GRID_SIZE> ligth_grid;
    std::vector<int32_t> ligth_grid2(LIGTH_GRID_SIZE * LIGTH_GRID_SIZE, 0);

    ligth_grid.fill(false);

    while(std::optional<Inst> inst = Inst::get_next_inst_from_stream(input)){
        Inst val = inst.value();
        val.apply_to(ligth_grid);
        val.apply_to(ligth_grid2);
        //std::cout << inst.value() << " - " << sum_ligths(ligth_grid2) << "\n";
    }

    size_t lcount = count_ligths(ligth_grid);
    size_t lsum = sum_ligths(ligth_grid2);

    std::cout << "Part1:\n" << "    ligths on: " << lcount << "\n";
    std::cout << "Part2:\n" << "    total brigth: " << lsum << "\n";

    return 0;
}
