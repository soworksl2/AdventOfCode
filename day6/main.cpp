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
constexpr size_t INST_LINE_BUFFER_SIZE = 1000;

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

class Range{
private:
    Vector2d m_start;
    Vector2d m_end;
public:
    Range(Vector2d start, Vector2d end)
    : m_start{start}, m_end{end}
    {}

    friend std::ostream& operator<<(std::ostream& os, const Range& val);
};
std::ostream& operator<<(std::ostream& os, const Range& val){
    os << val.m_start << " through " << val.m_end;
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

private:
    static std::string_view extract_operation_from_line(const std::string_view line, InstOp& op){
        constexpr std::string_view toogle{"toogle"};
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
        return extract_number_from_line(next_part, out.y);
    }

    static Range extract_range_from_line(const std::string_view line){
        constexpr std::string_view through{"through"};

        Vector2d start, end;
        std::string_view next_part = extract_vect2d_from_line(line, start);
        next_part.remove_prefix(1 + through.size() + 1);
        extract_vect2d_from_line(next_part, end);
        return {start, end};
    }
};
std::ostream& operator<<(std::ostream& os, const Inst& val){
    switch(val.m_op){
        case InstOp::TOOGLE:
            os << "toogle";
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

int main(){
    std::ifstream input{"input.txt"};
    std::array<bool, LIGTH_GRID_SIZE * LIGTH_GRID_SIZE> ligth_grid;
    std::vector<int32_t> ligth_grid2{LIGTH_GRID_SIZE * LIGTH_GRID_SIZE, 0};

    ligth_grid.fill(false);

    while(std::optional<Inst> inst = Inst::get_next_inst_from_stream(input)){
        std::cout << inst.value() << "\n";
    }

    return 0;
}
