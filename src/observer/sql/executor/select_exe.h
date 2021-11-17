#ifndef __OBSERVER_SQL_SELECT_EXE_H__
#define __OBSERVER_SQL_SELECT_EXE_H__

#include<vector>
#include<string>
#include<cstring>
#include<unordered_map>
#include<algorithm>
#include<set>

#include "sql/parser/parse_defs.h"

typedef struct Schema_Info{
    int offset;                 //找到offset
    int len;                    //读多长
    AttrType type;              //转化为什么类型
}Schema_Info;

// typedef struct Group_Res{
//     int count;
//     void *maxx;
//     void *minn;
//     void *avg;
// };

class SelectExe{

    public:
        SelectExe(SelectExe *father_selectexe);
        ~SelectExe();

        

        RC splice_table(std::string* temp, int i, int j);

        RC judge_condition(Condition_Composite* condition, std::string* x, int i, bool* res);

        RC compute_expression(Expression* exp, std::string* s, void *result, AttrType* tp);
        RC SelectExe_read_record(Trx *trx, const Selects &selects, const char *db);
        RC add_schameInfo_into_map(const char *relation_name);

        RC SelectExe_init(Db *datebase, const Selects &selects, Trx *trx);
        void insert_field_from_table(Table *table, int flag);
        RC check_select(const Selects &selects);
        RC check_condition_valid(Condition_Composite *condition);
        RC check_expression(Expression *expression);
        RC check_join(const JoinOn *joinon);
        void build_schameInfo_map(const Selects &selects);
        void do_order_by(std::vector<char *> &records);
        void do_group_by(std::vector<char *> &records);

        RC load_records_and_schames(const Selects select);
        RC load_records_from_table(const char *relation_name);
        RC combain_table(int is_select, int join_num);
        RC combain_table();
        void show_schame_map();
        RC show_records();
        int group_cmp(const GroupBy *groupby, char *left, char *right);
        std::vector<std::vector<int>> group_index_result;
        std::vector<char *> vec_records;//存放做完筛选的元祖
        RC calculate_result();
        RC get_expression_results(std::vector<std::vector<void *>> &values_vec, Expression *expression, int group_index, AttrType &res_type);
        RC calculate_expression(std::vector<void *> &values_vec,Expression *expression,int group_index,AttrType &res_type,int deep);
        RC calculate_con_expression(std::vector<void *> &res_vec, Expression *expression ,AttrType &attr, char *data_res);
        RC terminal_select(std::vector<std::vector<void *>> &select_ress, std::vector<AttrType> &type, std::vector<std::string> &select_res_fields);
        std::vector<std::string> *terminal_fields;
        std::vector<AttrType> *terminal_type;
        void load_terminal_fields();
        void get_expression_name(std::string &str_name, Expression *expression, int deep);
    private:
        
        std::vector<char *> middle_records;//存放筛选过程中产生的元祖
        const Selects *select;
        
        int tmp_total_len;

        RC combain(char *data_res, int table_num,int is_select, int join_num, int tmp_len);
        RC condition_filter(bool &is_ok, Condition_Composite *condition, char *data_res);
        //std::unordered_map<std::string, Schema_Info> single_table_schema_info;         //存放无表名的offset
        std::unordered_map<std::string, Schema_Info> table_schema_info;           //存放带表名的offset
        std::vector<std::string> tupleset;
        
        std::vector<std::vector<char *>> tables_records;
        std::vector<int> table_record_length;
        int total_offset = 0; //
        int combain_deep = 0; //用于回收内存， 当deep=0时， 指向的时BP内char*不可回收

        bool has_group = false; //表示进行过分组
        std::unordered_map<std::string, AttrType> field_set;
        std::map<std::string, Schema_Info> table_map;
        std::vector<std::string> viewed_table;

        Trx *trx;
        Db * datebase;
        std::vector<std::vector<void *>> *select_ress;
        int field_id = 0; //show field_id;
        std::map<std::string, int> added_fields;

        SelectExe *father_selectexe;
        char *tmp_char_date;
};

#endif //__OBSERVER_SQL_SELECT_EXE_H__