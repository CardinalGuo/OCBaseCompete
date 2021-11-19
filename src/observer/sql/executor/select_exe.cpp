//
// Created by gpc on 2021/11/06.
//
#include <unordered_map>
#include <unordered_set>
#include "storage/common/table.h"

#include "storage/common/table_meta.h"
#include "storage/common/field_meta.h"
#include "storage/default/default_handler.h"
#include "storage/common/record_manager.h"
#include "sql/executor/select_exe.h"
#include "storage/common/check_trans.h"
//using namespace common;

SelectExe::SelectExe(SelectExe *father_selectexe)
{
    this->father_selectexe = father_selectexe;
    // table_record = {};
    // single_table_schema_info = {};
    // muti_table_schema_info = {};
    // tupleset = {};
}

SelectExe::~SelectExe()
{
}

RC SelectExe::check_expression(Expression *expression)
{
    if (expression->is_leaf == 1)
    {
        //LOG_INFO("check exp_info");
        if (expression->is_attr)
        {
            bool get_attr = true;
            std::string str_name = "";
            const RelAttr *relattr = &expression->attr;
            if (relattr->relation_name != nullptr)
                str_name.append(relattr->relation_name).append(".");
            str_name.append(relattr->attribute_name);
            //LOG_INFO("%s", str_name.c_str());
            if (field_set.find(str_name) == field_set.end())
            {
                get_attr = false;
                SelectExe *pointer = father_selectexe;
                while (pointer != nullptr)
                {
                    if (pointer->field_set.find(str_name) != pointer->field_set.end())
                    {
                        get_attr = true;
                        break;
                    }
                    else
                    {
                        pointer = pointer->father_selectexe;
                    }
                }
            }

            if (!get_attr)
                return RC::INVALID_ARGUMENT;
            //LOG_INFO("check exp_info ok");
        }
    }
    else
    {
        ////LOG_INFO("check count");
        RC rc_left = expression->left == nullptr ? RC::SUCCESS : check_expression(expression->left);
        ////LOG_INFO("check count ok");
        if (rc_left != RC::SUCCESS)
            return RC::INVALID_ARGUMENT;

        RC rc_right = (expression->right == nullptr ? RC::SUCCESS : check_expression(expression->right));
        if (rc_right != RC::SUCCESS)
            return RC::INVALID_ARGUMENT;
    }
    return RC::SUCCESS;
}

RC SelectExe::check_condition_valid(Condition_Composite *condition)
{
    RC rc = RC::SUCCESS;
    if (condition->left != nullptr)
        rc = check_expression(condition->left);
    if (rc != SUCCESS)
        return RC::INVALID_ARGUMENT;
    if (condition->right != nullptr)
        rc = check_expression(condition->right);
    if (rc != SUCCESS)
        return RC::INVALID_ARGUMENT;
    if (condition->select_attr_left != nullptr)
        rc = check_select(*(Selects *)condition->select_attr_left);
    if (rc != SUCCESS)
        return RC::INVALID_ARGUMENT;
    if (condition->select_attr_right != nullptr)
        rc = check_select(*(Selects *)condition->select_attr_right);
    if (rc != SUCCESS)
        return RC::INVALID_ARGUMENT;
    return RC::SUCCESS;
}

RC SelectExe::check_join(const JoinOn *joinon)
{
    RC rc = RC::SUCCESS;
    for (size_t i = 0; i < joinon->condition_num; i++)
    {
        Condition_Composite *condition = joinon->conditions[i];
        rc = check_condition_valid(condition);
        if (rc != SUCCESS)
            return RC::INVALID_ARGUMENT;
    }
    return RC::SUCCESS;
}

void SelectExe::insert_field_from_table(Table *table, int flag)
{
    const char *table_name = table->name();
    ////LOG_INFO("%s",table_name);
    const TableMeta &table_meta = table->table_meta();
    const int field_num = table_meta.field_num();
    std::string str_name = "";
    for (int i = 0; i < field_num; i++)
    {
        const FieldMeta *field_meta = table_meta.field(i);
        if (field_meta->visible())
        {
            str_name = "";
            str_name.append(table_name).append(".").append(field_meta->name());
            field_set[str_name] = field_meta->type();
            ////LOG_INFO("%s",str_name.c_str());
            if (flag)
            {
                str_name = "";
                str_name.append(field_meta->name());
                field_set[str_name] = field_meta->type();
            }
        }
    }
    str_name = "";
    str_name.append(table_name).append(".").append("*");
    field_set[str_name] = UNDEFINED;
    str_name = "*";
    field_set[str_name] = UNDEFINED;
}

RC SelectExe::check_select(const Selects &selects)
{
    RC rc = RC::SUCCESS;
    Db *datebase = this->datebase;

    //LOG_INFO("check table");
    for (size_t i = 0; i < selects.relation_num; i++)
    {
        //LOG_INFO("%d", selects.relation_num);
        if (nullptr == datebase->find_table(selects.relations[i]))
            return RC::INVALID_ARGUMENT;
    }
    // add field name into set

    //LOG_INFO("add field name into set");
    if (selects.join_num_max > 0)
    {
        if (selects.relation_num != 1)
        {
            return RC::INVALID_ARGUMENT;
        }
        Table *table = datebase->find_table(selects.relations[0]);
        insert_field_from_table(table, 0);
    }
    else
    {
        for (size_t i = 0; i < selects.relation_num; i++)
        {
            Table *table = datebase->find_table(selects.relations[i]);
            if (selects.relation_num == 1)
            {
                insert_field_from_table(table, 1);
            }
            else
            {
                insert_field_from_table(table, 0);
            }
        }

        // SelectExe *pointer = this->father_selectexe;
        // while (pointer != nullptr)
        // {
        //     for (size_t i = 0; i < pointer->select->relation_num; i++)
        //     {
        //         Table *table = datebase->find_table(pointer->select->relations[i]);
        //         insert_field_from_table(table, 0);
        //     }
        //     pointer = pointer->father_selectexe;
        // }
    }

    //LOG_INFO("check_join %d", selects.join_num_max - 1);
    for (int i = 0; i < selects.join_num_max; i++)
    {
        Table *table = datebase->find_table(selects.join_on[i].relation_name);
        std::string str_name = "";
        str_name.append(selects.join_on[i].relation_name).append(".").append("*");
        //LOG_INFO("%s", str_name.c_str());
        if (field_set.find(str_name) != field_set.end())
            return RC::INVALID_ARGUMENT;
        insert_field_from_table(table, 0);
        rc = check_join(&selects.join_on[i]);
        if (rc != SUCCESS)
            return RC::INVALID_ARGUMENT;
    }

    //LOG_INFO("check show_select");
    for (size_t i = 0; i < selects.expression_select_num; i++)
    {
        //LOG_INFO("%d total num", (int)selects.expression_select_num);
        Expression *expre_tmp = selects.expression_select[i];
        rc = check_expression(expre_tmp);
        if (rc != SUCCESS)
            return RC::INVALID_ARGUMENT;
    }
    //LOG_INFO("check condition");
    //LOG_INFO("check condition %d", selects.condition_num);
    for (size_t i = 0; i < selects.condition_num; i++)
    {
        Condition_Composite *condition = selects.conditions[i];
        rc = check_condition_valid(condition);
        if (rc != SUCCESS)
            return RC::INVALID_ARGUMENT;
    }

    //LOG_INFO("check group");
    const GroupBy *groupby = &selects.group_by;
    for (size_t i = 0; i < groupby->attr_num; i++)
    {
        const RelAttr *relattr = &groupby->attributes[i];
        std::string str_name = "";
        if (relattr->relation_name != nullptr)
            str_name.append(relattr->relation_name).append(".");
        str_name.append(relattr->attribute_name);
        if (field_set.find(str_name) == field_set.end())
            return RC::INVALID_ARGUMENT;
    }

    //LOG_INFO("check order");
    const OrderBy *orderby = &selects.order_by;
    for (size_t i = 0; i < orderby->attr_num; i++)
    {
        const RelAttr *relattr = &orderby->attributes[i];
        std::string str_name = "";
        if (relattr->relation_name != nullptr)
            str_name.append(relattr->relation_name).append(".");
        str_name.append(relattr->attribute_name);
        if (field_set.find(str_name) == field_set.end())
            return RC::INVALID_ARGUMENT;
    }
    return rc;
}

void SelectExe::do_order_by(std::vector<char *> &records)
{

    const OrderBy *orderby = &(select->order_by);
    if (select->order_by.attr_num == 0)
        return;
    std::map<std::string, Schema_Info> table_map = this->table_map;
    std::sort(records.begin(), records.end(), [orderby, table_map](char *left, char *right) {
        // int left_null = 1;
        // int right_null = 1;
        // char *left_value = left.c_str();
        // char *right_value = left.c_str();
        // if (0 == strcmp(left_value, "GAY")) left_null = 0;
        // if (0 == strcmp(right_value, "GAY")) right_null = 0;

        // if (left_null || right_null) return (left_null - right_null)

        for (int i = orderby->attr_num - 1; i >= 0; i--)
        {
            std::string name;
            if (orderby->attributes[i].relation_name != nullptr)
                name.append(orderby->attributes[i].relation_name).append(".");
            name.append(orderby->attributes[i].attribute_name);

            Schema_Info schema_tmp = table_map.find(name)->second;
            int attr_offset = schema_tmp.offset;
            AttrType type_tmp = schema_tmp.type;

            ////LOG_INFO("%d %d",attr_offset, type_tmp);
            char *left_value = left + attr_offset;
            char *right_value = right + attr_offset;

            switch (type_tmp)
            {
            case DATES:
            case INTS:
            {
                int left_val = *(int *)left_value;
                int right_val = *(int *)right_value;
                if (left_val != right_val)
                    return orderby->up_or_down[i] == 0 ? left_val > right_val : left_val < right_val;
                break;
            }
            case FLOATS:
            {
                float left_val = *(float *)left_value;
                float right_val = *(float *)right_value;
                if (left_val != right_val)
                    return orderby->up_or_down[i] == 0 ? left_val > right_val : left_val < right_val;
                break;
            }

            case CHARS:
            {
                int compare_result = strcmp(left_value, right_value);
                if (compare_result != 0)
                    return orderby->up_or_down[i] == 0 ? compare_result > 0 : compare_result < 0;
                break;
            }
            default:
                break;
            }
        }
        return true;
    });
}
void free_vector(std::vector<char *> &vec)
{

    for (size_t i = 0; i < vec.size(); i++)
    {
        free(vec[i]);
    }
    vec.clear();
}
void free_vector(std::vector<void *> &vec, int num)
{
    for (size_t i = 1; i < vec.size(); i++)
    {
        free(vec[i]);
    }
    vec.clear();
}
void free_vector(std::vector<void *> &vec)
{

    for (size_t i = 0; i < vec.size(); i++)
    {
        free(vec[i]);
    }
    vec.clear();
}

int SelectExe::group_cmp(const GroupBy *groupby, char *left, char *right)
{

    for (int i = groupby->attr_num - 1; i >= 0; i--)
    {
        std::string str = "";
        if (groupby->attributes[i].relation_name != nullptr)
            str.append(groupby->attributes[i].relation_name).append(".");
        str.append(groupby->attributes[i].attribute_name);
        int offset = table_map[str].offset;
        AttrType attr = table_map[str].type;
        switch (attr)
        {
        case DATES:
        case INTS:
            if (*(int *)(left + offset) != *(int *)(right + offset))
                return 1;
            break;
        case FLOATS:
            if (*(float *)(left + offset) != *(float *)(right + offset))
                return 1;
            break;

        case CHARS:
            if (strcmp((left + offset), (right + offset)) != 0)
                return 1;
            break;
        default:
            break;
        }
    }
    return 0;
}
void SelectExe::do_group_by(std::vector<char *> &records)
{
    const GroupBy *groupby = &(select->group_by);
    if (groupby->attr_num > 0)
    {
        has_group = true;
    }
    else
    {
        has_group = false;
    }
    for (size_t i = 0; i < records.size(); i++)
    {
        bool find_group = false;
        for (size_t j = 0; j < group_index_result.size(); j++)
        {
            int first_index = group_index_result[j][0];
            if (0 == group_cmp(groupby, records[i], records[first_index]))
            {
                find_group = true;
                group_index_result[j].push_back(i);
            }
        }
        if (!find_group)
        {
            std::vector<int> set_tmp;
            set_tmp.push_back(i);
            group_index_result.push_back(set_tmp);
        }
    }
}

//max == 1 min == 0;
void get_max_min_value(std::vector<void *> &left, AttrType attr_left, std::vector<void *> &values_vec, int max_min)
{
    char not_null = '0';
    void *value;
    bool get_unit = false;
    switch (attr_left)
    {
    case INTS:
    {
        size_t index = 0;
        while (index < left.size())
        {
            if (!get_unit)
            {
                if ('0' == *((char *)left[index]) + 4 * sizeof(char))
                {
                    value = malloc(sizeof(char) * 5);
                    memcpy(value, left[index], sizeof(int));

                    memcpy(value + 4 * sizeof(char), &not_null, sizeof(char));
                    get_unit = true;
                }
            }
            else
            {
                if ('0' == *((char *)left[index]) + 4 * sizeof(char))
                {
                    int sub_v = *(int *)value - *(int *)left[index];

                    if (sub_v * max_min < 0)
                    {
                        memcpy(value, left[index], sizeof(int));
                    }
                }
            }
            index++;
        }
    }
    break;
    case FLOATS:
    {
        size_t index = 0;
        while (index < left.size())
        {
            if (!get_unit)
            {
                if ('0' == *((char *)left[index]) + 4 * sizeof(char))
                {
                    value = malloc(sizeof(char) * 5);
                    memcpy(value, left[index], sizeof(int));

                    memcpy(value + 4 * sizeof(char), &not_null, sizeof(char));
                    get_unit = true;
                }
            }
            else
            {
                if ('0' == *((char *)left[index]) + 4 * sizeof(char))
                {
                    float sub_v = *(float *)value - *(float *)left[index];
                    if (sub_v * max_min < 0)
                    {
                        memcpy(value, left[index], sizeof(float));
                    }
                }
            }
            index++;
        }
    }
    break;
    case DATES:
    {
        size_t index = 0;
        while (index < left.size())
        {
            if (!get_unit)
            {
                if ('0' == *((char *)left[index]) + 4 * sizeof(char))
                {
                    value = malloc(sizeof(char) * 5);
                    memcpy(value, left[index], sizeof(int));

                    memcpy(value + 4 * sizeof(char), &not_null, sizeof(char));
                    get_unit = true;
                }
            }
            else
            {
                if ('0' == *((char *)left[index]) + 4 * sizeof(char))
                {
                    int cmp = *(int *)value - *(int *)left[index];
                    if (cmp * max_min < 0)
                    {
                        memcpy(value, left[index], sizeof(int));
                    }
                }
            }
            index++;
        }
    }
    break;
    case CHARS:
    {
        size_t index = 0;
        while (index < left.size())
        {
            if (!get_unit)
            {
                if ('0' == *((char *)left[index]) + 4 * sizeof(char))
                {
                    value = malloc(sizeof(char) * 5);
                    memcpy(value, left[index], sizeof(int));

                    memcpy(value + 4 * sizeof(char), &not_null, sizeof(char));
                    get_unit = true;
                }
            }
            else
            {
                if ('0' == *((char *)left[index]) + 4 * sizeof(char))
                {
                    int cmp = strcmp((char *)value, (char *)left[index]);
                    if (cmp * max_min < 0)
                    {
                        memcpy(value, left[index], sizeof(int));
                    }
                }
            }
            index++;
        }
    }
    break;
    default:
        break;
    }
    if (get_unit)
        values_vec.push_back(value);
}

RC SelectExe::calculate_expression(std::vector<void *> &values_vec, Expression *expression, int group_index, AttrType &res_type, int deep)
{
    RC rc = RC::SUCCESS;
    if (expression->is_leaf)
    {
        if (expression->is_attr)
        {
            std::string name = "";
            if (expression->attr.relation_name != nullptr)
                name.append(expression->attr.relation_name).append(".");
            name.append(expression->attr.attribute_name);

            if (0 == strcmp(expression->attr.attribute_name, "*"))
            {
                res_type = UNDEFINED;
                if (deep == 1)
                {
                    if (expression->attr.relation_name == nullptr)
                    {
                        for (auto it : viewed_table)
                        {
                            Table *table = datebase->find_table(it.c_str());
                            const TableMeta &table_meta = table->table_meta();
                            const int field_num = table_meta.field_num();
                            for (int i = 0; i < field_num; i++)
                            {

                                const FieldMeta *field_meta = table_meta.field(i);

                                if (!field_meta->visible())
                                    continue;
                                int field_id_tmp = 0;
                                std::string tmp_field_name = "";
                                tmp_field_name.append(table_meta.name()).append(".").append(field_meta->name());

                                //LOG_INFO("view field %s", tmp_field_name.c_str());

                                Schema_Info *schema_info = &table_map[tmp_field_name];

                                if (added_fields.find(tmp_field_name) == added_fields.end())
                                {
                                    std::vector<void *> tmp_vec;
                                    select_ress->push_back(tmp_vec);
                                    //LOG_INFO("add new type into res %d", schema_info->type);
                                    added_fields[tmp_field_name] = field_id;
                                    terminal_type->push_back(schema_info->type);
                                    field_id_tmp = field_id;
                                    field_id++;
                                }
                                else
                                {
                                    field_id_tmp = added_fields[tmp_field_name];
                                }

                                for (size_t j = 0; j < group_index_result[group_index].size(); j++)
                                {
                                    void *value;
                                    value = malloc(schema_info->len * sizeof(char));
                                    int index = group_index_result[group_index][j];
                                    value = memcpy(value, (vec_records[index]) + schema_info->offset, schema_info->len * sizeof(char));
                                    (*select_ress)[field_id_tmp].push_back(value);
                                    if (has_group)
                                    {
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        Table *table = datebase->find_table(expression->attr.relation_name);
                        const TableMeta &table_meta = table->table_meta();
                        const int field_num = table_meta.field_num();

                        for (int i = 0; i < field_num; i++)
                        {

                            const FieldMeta *field_meta = table_meta.field(i);
                            if (!field_meta->visible())
                                continue;
                            int field_id_tmp = 0;
                            std::string tmp_field_name = "";
                            tmp_field_name.append(expression->attr.relation_name).append(".").append(field_meta->name());

                            Schema_Info *schema_info = &table_map[tmp_field_name];

                            if (added_fields.find(tmp_field_name) == added_fields.end())
                            {
                                std::vector<void *> tmp_vec;
                                select_ress->push_back(tmp_vec);
                                //LOG_INFO("add new type into res %d", schema_info->type);
                                terminal_type->push_back(schema_info->type);
                                field_id_tmp = field_id;
                                field_id++;
                            }
                            else
                            {
                                field_id_tmp = added_fields[tmp_field_name];
                            }

                            for (size_t j = 0; j < group_index_result[group_index].size(); j++)
                            {
                                void *value;
                                value = malloc(schema_info->len * sizeof(char));
                                int index = group_index_result[group_index][j];
                                value = memcpy(value, (vec_records[index]) + schema_info->offset, schema_info->len * sizeof(char));
                                (*select_ress)[field_id_tmp].push_back(value);
                                //LOG_INFO("has group ?%d", has_group);
                                if (has_group)
                                {
                                    break;
                                }
                            }
                        }
                    }
                }
                else
                {
                    // only count can operate like this
                    res_type = UNDEFINED;
                    for (size_t i = 0; i < group_index_result[group_index].size(); i++)
                    {
                        void *value = malloc(sizeof(char));
                        values_vec.push_back(value);
                    }
                }
                return RC::SUCCESS;
            }
            else
            {

                Schema_Info *schema_info = &table_map[name];
                res_type = schema_info->type;
                for (size_t i = 0; i < group_index_result[group_index].size(); i++)
                {
                    void *value;
                    value = malloc(schema_info->len * sizeof(char));
                    int index = group_index_result[group_index][i];
                    value = memcpy(value, (vec_records[index]) + schema_info->offset, schema_info->len * sizeof(char));
                    //LOG_INFO("add  %d %d", *(int *)value, group_index);
                    values_vec.push_back(value);
                }
            }
        }
        else
        {
            for (size_t i = 0; i < group_index_result[group_index].size(); i++)
            {
                void *value;
                res_type = expression->value.type;
                switch (res_type)
                {
                case INTS:
                    value = malloc(sizeof(int));
                    memcpy(value, expression->value.data, sizeof(int));
                    break;
                case FLOATS:
                    value = malloc(sizeof(float));
                    memcpy(value, expression->value.data, sizeof(float));
                    break;
                case DATES:
                    value = strdup((char *)expression->value.data);
                    break;
                case CHARS:
                    value = strdup((char *)expression->value.data);
                    break;
                default:
                    break;
                }

                values_vec.push_back(value);
            }
        }
    }
    else
    {
        std::vector<void *> left;
        std::vector<void *> right;
        AttrType attr_left, attr_right;

        bool finish = true;
        if (expression->left != nullptr)
            rc = calculate_expression(left, expression->left, group_index, attr_left, deep + 1);
        if (rc != RC::SUCCESS)
        {
            finish = false;
        }
        if (expression->right != nullptr)
            calculate_expression(right, expression->right, group_index, attr_right, deep + 1);
        if (rc != RC::SUCCESS)
        {
            finish = false;
        }
        if (finish == false)
        {
            free_vector(left);
            free_vector(right);
            return RC::INVALID_ARGUMENT;
        }

        switch (expression->calculate)
        {

        case CAL_COUNT:
        {
            void *value;
            value = malloc(sizeof(char) * 5);
            int sum = 0;
            char not_null = '0';
            memcpy(value + 4 * sizeof(char), &not_null, sizeof(not_null));
            //LOG_INFO("%d", sum);

            res_type = INTS;
            for (auto it : left)
            {
                switch (attr_left)
                {
                case INTS:
                case FLOATS:
                case DATES:
                case CHARS:
                {
                    if ('0' != *((char *)it + 4 * sizeof(char)))
                    {
                        sum++;
                    }
                }
                break;
                case TEXTS:
                {
                    if ('0' != *((char *)it + 12 * sizeof(char)))
                    {
                        sum++;
                    }
                }
                break;
                default:
                    break;
                }
            }
            memcpy(value, &sum, sizeof(sum));

            values_vec.push_back(value);
            break;
        }
        case CAL_ADD:
        case CAL_SUB:
        case CAL_MUL:
        case CAL_DIV:
        {
            ////LOG_INFO("%d %d", attr_left, attr_right);
            if (attr_left == UNDEFINED || attr_right == UNDEFINED)
            {
                finish = false;
                break;
            }
            if ((attr_left != INTS && attr_left != FLOATS) || (attr_right != INTS && attr_right != FLOATS))
            {
                finish = false;
                break;
            }
            if (attr_left == FLOATS || attr_right == FLOATS)
                res_type = FLOATS;
            else
                res_type = INTS;

            for (size_t i = 0; i < left.size() && i < right.size(); i++)
            {
                void *value;
                ////LOG_INFO("%d %d %d %d", (int)left.size(), (int)right.size(), finish, res_type);
                if (res_type == FLOATS)
                {
                    float sum = 0;
                    value = malloc(sizeof(float));
                    if (attr_left == FLOATS)
                    {
                        sum += *(float *)left[i];
                    }
                    else
                    {
                        int tmp = *(int *)left[i];
                        sum += (float)tmp;
                    }
                    float l_f = 0.0;
                    if (attr_right == FLOATS)
                    {
                        l_f = *(float *)right[i];
                    }
                    else
                    {
                        int tmp = *(int *)right[i];
                        l_f = (float)tmp;
                    }

                    switch (expression->calculate)
                    {
                    case CAL_ADD:
                        sum += l_f;
                        break;
                    case CAL_SUB:
                        sum -= l_f;
                        break;
                    case CAL_MUL:
                        sum *= l_f;
                        break;
                    case CAL_DIV:
                        if (l_f == 0.0)
                        {
                            finish = false;
                            break;
                        }
                        else
                            sum /= l_f;
                        break;

                    default:
                        break;
                    }
                    memcpy(value, &sum, sizeof(sum));
                }
                else
                {
                    int sum = 0;
                    float sum_f = 0.0;
                    value = malloc(sizeof(int));
                    switch (expression->calculate)
                    {
                    case CAL_ADD:
                    {
                        sum = *(int *)left[i] + *(int *)right[i];
                        ////LOG_INFO("%d %d %d  ", sum, *(int *)left[i], *(int *)right[i]);
                        break;
                    }
                    case CAL_SUB:
                    {
                        sum = *(int *)left[i] - *(int *)right[i];
                        break;
                    }
                    case CAL_MUL:
                    {
                        sum = *(int *)left[i] * *(int *)right[i];
                        break;
                    }
                    case CAL_DIV:
                    {
                        res_type = FLOATS;

                        int r_v = *(int *)right[i];
                        if (r_v == 0)
                        {
                            finish = false;
                            break;
                        }
                        else
                            sum_f = (float)(*(int *)left[i]) / (float)r_v;
                        break;
                    }
                    default:
                        break;
                    }
                    if (res_type == INTS)
                        memcpy(value, &sum, sizeof(sum));
                    else
                        memcpy(value, &sum_f, sizeof(sum_f));
                }
                values_vec.push_back(value);
            }
            break;
        }
        case CAL_MAX:
            if (attr_left == UNDEFINED)
            {
                finish = false;
                break;
            }
            res_type = attr_left;
            if (left.size() > 0)
            {
                get_max_min_value(left, attr_left, values_vec, 1);
            }
            break;
        case CAL_MIN:
            if (attr_left == UNDEFINED)
            {
                finish = false;
                break;
            }
            res_type = attr_left;
            if (left.size() > 0)
            {
                get_max_min_value(left, attr_left, values_vec, -1);
            }
            break;
        case CAL_AVG:
            if (attr_left == UNDEFINED || attr_left == CHARS)
            {
                finish = false;
                break;
            }
            if (attr_left == DATES)
            {
                res_type = INTS;
                if (left.size() > 0)
                {
                    void *value = malloc(sizeof(int));
                    bool get_num = false;
                    int avg_int = 0;
                    int sz = 0;
                    for (size_t index = 0; index < left.size(); index++)
                    {
                        if (*((char *)left[index] + 4 * sizeof(char)) == '0')
                        {
                            sz++;
                            avg_int += *(int *)left[index];
                            get_num = true;
                        }
                    }
                    if (get_num)
                    {
                        ////LOG_INFO("%f",avg);
                        memcpy(value, &avg_int, sizeof(avg_int));
                        values_vec.push_back(value);
                    }
                }
            }
            else
            {
                res_type = FLOATS;
                if (left.size() > 0)
                {
                    void *value = malloc(sizeof(int));
                    int avg_int = 0;
                    bool get_num = false;
                    float avg_float = 0.0;
                    int sz = 0;
                    for (size_t index = 0; index < left.size(); index++)
                    {
                        if (*((char *)left[index] + 4 * sizeof(char)) == '0')
                        {
                            sz++;
                            get_num = true;
                            if (attr_left == INTS)
                                avg_int += *(int *)left[index];
                            if (attr_left == FLOATS)
                                avg_float += *(float *)left[index];
                        }
                    }
                    if (get_num)
                    {
                        float avg = attr_left == INTS ? (float)(avg_int) / (float)(sz) : avg_float / (float)sz;
                        res_type = FLOATS;
                        ////LOG_INFO("%f",avg);
                        memcpy(value, &avg, sizeof(avg));
                        values_vec.push_back(value);
                    }
                }
            }

            break;

        case CAL_IDEO:
            break;
        case CAL_SELF:
        {
            res_type = attr_left;
            for (size_t i = 0; i < left.size(); i++)
            {
                void *value;
                res_type = attr_left;
                switch (res_type)
                {
                case INTS:
                {
                    value = malloc(sizeof(int));
                    memcpy(value, left[i], sizeof(int));
                }
                break;
                case FLOATS:
                {
                    value = malloc(sizeof(float));
                    memcpy(value, left[i], sizeof(int));
                }
                break;
                case CHARS:
                {
                    value = strdup((char *)left[i]);
                }
                break;
                case DATES:
                {
                    value = malloc(sizeof(int));
                    memcpy(value, left[i], sizeof(int));
                }
                break;
                case EMPTY_TYPE:
                {
                }
                break;
                default:
                    break;
                }
                values_vec.push_back(value);
            }
        }
        break;
        case CAL_MINUS:
        {

            res_type = attr_left;
            for (size_t i = 0; i < left.size(); i++)
            {
                void *value;
                if (attr_left == EMPTY_TYPE)
                {
                    break;
                }

                if (attr_left != FLOATS && attr_left != INTS)
                {
                    finish = false;
                    break;
                }
                else
                {

                    if (attr_left == FLOATS)
                    {
                        value = malloc(sizeof(float));
                        float tmp_float = -1.0 * (*(float *)left[i]);
                        memcpy(value, &tmp_float, sizeof(tmp_float));
                    }
                    else
                    {
                        value = malloc(sizeof(int));
                        int tmp_int = -1.0 * (*(int *)left[i]);
                        memcpy(value, &tmp_int, sizeof(tmp_int));
                    }
                }
                values_vec.push_back(value);
            }
        }
        break;
        default:
            break;
        }
        if (!finish)
            rc = RC::INVALID_ARGUMENT;

        //LOG_INFO("free left_right expression_value");
        free_vector(left);
        free_vector(right);
    }

    return rc;
}
RC SelectExe::calculate_result()
{

    for (size_t i = 0; i < group_index_result.size(); i++)
    {
        //std::vector<void *> record_values;
        ///////////////////////////  terminal_res at field i

        for (int j = select->expression_select_num - 1; j >= 0; j--)
        {
            AttrType type;
            std::vector<void *> value_res;
            //LOG_INFO("doing exp");
            RC rc = calculate_expression(value_res, select->expression_select[j], i, type, 1);
            if (type != UNDEFINED)
            {
                if (added_fields.find(std::to_string(j)) == added_fields.end())
                {
                    //LOG_INFO("add new type into res type = %d, field_=%s id = %d", type, std::to_string(j).c_str(), field_id);
                    added_fields[std::to_string(j)] = field_id;
                    std::vector<void *> empty_vec;
                    select_ress->push_back(empty_vec);
                    terminal_type->push_back(type);
                    field_id++;
                }
                int field_id_tmp = added_fields[std::to_string(j)];
                for (auto it : value_res)
                {

                    (*select_ress)[field_id_tmp].push_back(it);
                    //LOG_INFO("%d", *(int *)((*select_ress)[field_id_tmp][0]));
                    if (has_group)
                    {
                        free_vector(value_res, 1);
                        break;
                    }
                }
            }
            //LOG_INFO("finish exp");
            if (rc != RC::SUCCESS)
                return RC::INVALID_ARGUMENT;
            for (auto it : value_res)
            {
                switch (type)
                {
                case INTS:
                    //LOG_INFO("%d", *(int *)it);
                    break;

                case FLOATS:
                    //LOG_INFO("%f", *(float *)it);
                    break;

                case CHARS:
                    //LOG_INFO("%s", (char *)it);
                    break;

                case DATES:
                    //LOG_INFO("%d", *(int *)it);
                    break;

                default:
                    break;
                }
            }
            //record_values.push_back(value);
        }
    }
    return RC::SUCCESS;
}

RC SelectExe::calculate_con_expression(std::vector<void *> &res_vec, Expression *expression, AttrType &res_attr, char *data_res)
{
    RC rc = RC::SUCCESS;
    if (expression->is_leaf)
    {
        if (expression->is_attr)
        {
            std::string name = "";
            if (expression->attr.relation_name != nullptr)
                name.append(expression->attr.relation_name).append(".");
            name.append(expression->attr.attribute_name);

            if (0 == strcmp(expression->attr.attribute_name, "*"))
            {
                return RC::INVALID_ARGUMENT;
            }
            else
            {

                SelectExe *pointer = this;
                while (pointer != nullptr)
                {
                    //LOG_INFO("pointer finding ");
                    if (pointer->table_map.find(name) != pointer->table_map.end())
                    {
                        Schema_Info *schema_info = &(pointer->table_map[name]);
                        res_attr = schema_info->type;
                        //LOG_INFO("pointer find ");
                        void *value;
                        value = malloc(schema_info->len * sizeof(char));
                        value = memcpy(value, pointer->tmp_char_date + schema_info->offset, schema_info->len * sizeof(char));
                        if (*(pointer->tmp_char_date + schema_info->offset + schema_info->len * sizeof(char) - 1) == '1')
                        {
                            res_attr = NULL_TYPE;
                        }
                        res_vec.push_back(value);
                        break;
                    }
                    else
                    {
                        pointer = pointer->father_selectexe;
                    }
                }
            }
        }
        else
        {
            void *value;
            res_attr = expression->value.type;
            switch (res_attr)
            {
            case INTS:
                value = malloc(sizeof(int));
                memcpy(value, expression->value.data, sizeof(int));
                break;
            case FLOATS:
                value = malloc(sizeof(float));
                memcpy(value, expression->value.data, sizeof(float));
                break;
            case DATES:
                value = strdup((char *)expression->value.data);
                break;
            case CHARS:
                value = strdup((char *)expression->value.data);
                break;
            case NULL_TYPE:
                value = malloc(sizeof(char));
                break;
            default:
                break;
            }
            res_vec.push_back(value);
        }
    }
    else
    {
        std::vector<void *> left;
        std::vector<void *> right;
        AttrType attr_left, attr_right;

        bool finish = true;
        if (expression->left != nullptr)
            rc = calculate_con_expression(left, expression->left, attr_left, data_res);
        if (rc != RC::SUCCESS)
        {
            finish = false;
        }
        if (expression->right != nullptr)
            calculate_con_expression(right, expression->right, attr_right, data_res);
        if (rc != RC::SUCCESS)
        {
            finish = false;
        }

        if (finish == false)
        {
            free_vector(left);
            free_vector(right);
            return RC::INVALID_ARGUMENT;
        }
        //LOG_INFO("type  %d %d", attr_left, attr_right);
        switch (expression->calculate)
        {

        case CAL_ADD:
        case CAL_SUB:
        case CAL_MUL:
        case CAL_DIV:
        {
            if (attr_left == EMPTY_TYPE || attr_right == EMPTY_TYPE)
            {
                res_attr = EMPTY_TYPE;
            }
            ////LOG_INFO("%d %d", attr_left, attr_right);
            if (attr_left == UNDEFINED || attr_right == UNDEFINED)
            {
                finish = false;
                break;
            }
            if ((attr_left != INTS && attr_left != FLOATS) || (attr_right != INTS && attr_right != FLOATS))
            {
                finish = false;
                break;
            }
            if (attr_left == FLOATS || attr_right == FLOATS)
                res_attr = FLOATS;
            else
                res_attr = INTS;

            void *value;
            if (res_attr == FLOATS)
            {
                float sum = 0;
                value = malloc(sizeof(float));
                if (attr_left == FLOATS)
                {
                    sum += *(float *)left[0];
                }
                else
                {
                    int tmp = *(int *)left[0];
                    sum += (float)tmp;
                }
                float l_f = 0.0;
                if (attr_right == FLOATS)
                {
                    l_f = *(float *)right[0];
                }
                else
                {
                    int tmp = *(int *)right[0];
                    l_f = (float)tmp;
                }

                switch (expression->calculate)
                {
                case CAL_ADD:
                    sum += l_f;
                    break;
                case CAL_SUB:
                    sum -= l_f;
                    break;
                case CAL_MUL:
                    sum *= l_f;
                    break;
                case CAL_DIV:
                    if (l_f == 0.0)
                    {
                        res_attr = EMPTY_TYPE;
                        break;
                    }
                    else
                        sum /= l_f;
                    break;

                default:
                    break;
                }
                memcpy(value, &sum, sizeof(sum));
            }
            else
            {
                int sum = 0;
                float sum_f = 0.0;
                value = malloc(sizeof(int));
                switch (expression->calculate)
                {
                case CAL_ADD:
                {
                    sum = *(int *)left[0] + *(int *)right[0];
                    ////LOG_INFO("%d %d %d  ", sum, *(int *)left[i], *(int *)right[i]);
                    break;
                }
                case CAL_SUB:
                {
                    sum = *(int *)left[0] - *(int *)right[0];
                    break;
                }
                case CAL_MUL:
                {
                    sum = *(int *)left[0] * *(int *)right[0];
                    break;
                }
                case CAL_DIV:
                {
                    res_attr = FLOATS;

                    int r_v = *(int *)right[0];
                    if (r_v == 0)
                    {
                        res_attr = EMPTY_TYPE;
                        break;
                    }
                    else
                        sum_f = (float)(*(int *)left[0]) / (float)r_v;
                    break;
                }
                default:
                    break;
                }
                if (res_attr == INTS)
                    memcpy(value, &sum, sizeof(sum));
                else
                    memcpy(value, &sum_f, sizeof(sum_f));
            }
            res_vec.push_back(value);
            break;
        }
        case CAL_COUNT:
        case CAL_MAX:
        case CAL_MIN:
        case CAL_AVG:
            finish = false;
            break;
        case CAL_SELF:
        {
            void *value;
            res_attr = attr_left;
            switch (res_attr)
            {
            case INTS:
            {
                value = malloc(sizeof(int));
                memcpy(value, left[0], sizeof(int));
            }
            break;
            case FLOATS:
            {
                value = malloc(sizeof(float));
                memcpy(value, left[0], sizeof(int));
            }
            break;
            case CHARS:
            {
                value = strdup((char *)left[0]);
            }
            break;
            case DATES:
            {
                value = malloc(sizeof(int));
                memcpy(value, left[0], sizeof(int));
            }
            break;
            case EMPTY_TYPE:
            {
            }
            break;
            default:
                break;
            }
            res_vec.push_back(value);
        }
        break;
        case CAL_MINUS:
        {

            void *value;
            res_attr = attr_left;
            if (attr_left == EMPTY_TYPE)
            {
                break;
            }

            if (attr_left != FLOATS && attr_left != INTS)
            {
                finish = false;
                break;
            }
            else
            {

                if (attr_left == FLOATS)
                {
                    value = malloc(sizeof(float));
                    float tmp_float = -1.0 * (*(float *)left[0]);
                    memcpy(value, &tmp_float, sizeof(tmp_float));
                }
                else
                {
                    value = malloc(sizeof(int));
                    int tmp_int = -1.0 * (*(int *)left[0]);
                    memcpy(value, &tmp_int, sizeof(tmp_int));
                }
            }
            res_vec.push_back(value);
        }
        break;
        case CAL_IDEO:
            break;
        default:
            break;
        }
        if (!finish)
            rc = RC::INVALID_ARGUMENT;

        //LOG_INFO("free left_right_con_expression");
        free_vector(left);
        free_vector(right);
    }
    return rc;
}
RC SelectExe::add_schameInfo_into_map(const char *relation_name)
{
    Table *table = datebase->find_table(relation_name);
    for (int i = 0; i < viewed_table.size(); i++)
    {
        if (strcmp(viewed_table[i].c_str(), relation_name) == 0)
        {
            return RC::INVALID_ARGUMENT;
        }
    }
    viewed_table.push_back(relation_name);
    const TableMeta &table_meta = table->table_meta();
    const int field_num = table_meta.field_num();
    std::string table_name = table_meta.name();
    Schema_Info schema_tmp;
    int length_tmp = 0;
    for (int i = 0; i < field_num; i++)
    {

        const FieldMeta *field_meta = table_meta.field(i);
        schema_tmp.len = field_meta->len();
        length_tmp += field_meta->len();
        schema_tmp.offset = total_offset;
        total_offset += field_meta->len();
        schema_tmp.type = field_meta->type();
        ////LOG_INFO("%d %d %s" ,schema_tmp.len, schema_tmp.offset, field_meta->name());
        table_map[table_name + "." + field_meta->name()] = schema_tmp;
        ////LOG_INFO("%d",select->join_num_max);
        if (select->relation_num == 1 && select->join_num_max == 0)
            table_map[field_meta->name()] = schema_tmp;
    }
    //table_map[selects.relations[i]] = (int)i;
    table_record_length.push_back(length_tmp);

    return RC::SUCCESS;
}

void SelectExe::get_expression_name(std::string &str_name, Expression *expression, int deep)
{
    if (expression == nullptr)
        return;
    if (expression->is_leaf)
    {
        if (expression->is_attr)
        {
            std::string name = "";
            if (expression->attr.relation_name != nullptr)
                name.append(expression->attr.relation_name).append(".");
            name.append(expression->attr.attribute_name);

            if (0 == strcmp(expression->attr.attribute_name, "*"))
            {
                if (deep == 1)
                {
                    if (select->relation_num == 1 && select->join_num_max == 0)
                    {
                        std::string table_name;
                        table_name = select->relations[0];
                        Table *table = datebase->find_table(table_name.c_str());
                        const TableMeta &table_meta = table->table_meta();
                        const int field_num = table_meta.field_num();
                        for (int i = 0; i < field_num; i++)
                        {
                            const FieldMeta *field_meta = table_meta.field(i);
                            if (field_meta->visible())
                                terminal_fields->push_back(field_meta->name());
                        }
                    }
                    else
                    {
                        if (expression->attr.relation_name == nullptr)
                        {
                            for (auto it : viewed_table)
                            {
                                Table *table = datebase->find_table(it.c_str());
                                const TableMeta &table_meta = table->table_meta();
                                const int field_num = table_meta.field_num();
                                for (int i = 0; i < field_num; i++)
                                {
                                    const FieldMeta *field_meta = table_meta.field(i);
                                    ////LOG_INFO("view field %s %s", table_meta.name(),field_meta->name());
                                    if (field_meta->visible())
                                        terminal_fields->push_back(it + "." + field_meta->name());
                                }
                            }
                        }
                        else
                        {
                            Table *table = datebase->find_table(expression->attr.relation_name);
                            const TableMeta &table_meta = table->table_meta();
                            const int field_num = table_meta.field_num();
                            for (int i = 0; i < field_num; i++)
                            {
                                const FieldMeta *field_meta = table_meta.field(i);
                                if (field_meta->visible())
                                {
                                    std::string t_name = "";
                                    t_name.append(expression->attr.relation_name).append(".").append(field_meta->name());
                                    terminal_fields->push_back(t_name);
                                }
                            }
                        }
                    }
                }
                else
                {
                    str_name.append(name);
                }
            }
            else
            {
                if (select->relation_num == 1 && select->join_num_max == 0)
                    str_name.append(expression->attr.attribute_name);
                else
                    str_name.append(name);
            }
        }
        else
        {
            switch (expression->value.type)
            {
            case INTS:
            {

                int int_num = *(int *)expression->value.data;
                //LOG_INFO("load value %d ", int_num);
                str_name.append(std::to_string(int_num));
            }
            break;
            case FLOATS:
            {
                float float_num = *(float *)expression->value.data;
                str_name.append(std::to_string(float_num));
            }
            break;
            case DATES:
            {
                str_name.append((char *)expression->value.data);
            }
            break;
            case CHARS:
            {
                str_name.append((char *)expression->value.data);
            }
            break;
            default:
                break;
            }
        }
    }
    else
    {

        switch (expression->calculate)
        {
        case CAL_MINUS:
            str_name.append("-");
            str_name.append("(");
            get_expression_name(str_name, expression->left, deep + 1);
            str_name.append(")");
            break;
        case CAL_SELF:
            str_name.append("(");
            get_expression_name(str_name, expression->left, deep + 1);
            str_name.append(")");
            break;
        case CAL_ADD:
            get_expression_name(str_name, expression->left, deep + 1);
            str_name.append("+");
            get_expression_name(str_name, expression->right, deep + 1);
            break;
        case CAL_SUB:
            get_expression_name(str_name, expression->left, deep + 1);
            str_name.append("-");
            get_expression_name(str_name, expression->right, deep + 1);
            break;
        case CAL_MUL:

            get_expression_name(str_name, expression->left, deep + 1);
            str_name.append("*");
            get_expression_name(str_name, expression->right, deep + 1);

            break;
        case CAL_DIV:

            get_expression_name(str_name, expression->left, deep + 1);
            str_name.append("/");
            get_expression_name(str_name, expression->right, deep + 1);

            break;
        case CAL_COUNT:
            str_name.append("COUNT(");
            get_expression_name(str_name, expression->left, deep + 1);
            str_name.append(")");
            break;
        case CAL_MAX:
            str_name.append("MAX(");
            get_expression_name(str_name, expression->left, deep + 1);
            str_name.append(")");
            break;
        case CAL_MIN:
            str_name.append("MIN(");
            get_expression_name(str_name, expression->left, deep + 1);
            str_name.append(")");
            break;
        case CAL_AVG:
            str_name.append("AVG(");
            get_expression_name(str_name, expression->left, deep + 1);
            str_name.append(")");
            break;

        default:
            break;
        }
    }
}
void SelectExe::load_terminal_fields()
{
    for (int i = select->expression_select_num - 1; i >= 0; i--)
    {
        std::string str_name = "";
        get_expression_name(str_name, select->expression_select[i], 1);
        if (str_name != "")
        {
            terminal_fields->push_back(str_name);
            //LOG_INFO("%s", str_name.c_str());
        }
        else
        {
            //LOG_INFO("rela.* is added");
        }
    }
}
void SelectExe::build_schameInfo_map(const Selects &selects)
{
    for (size_t i = 0; i < selects.relation_num; i++)
    {
        add_schameInfo_into_map(selects.relations[i]);
    }
}

RC SelectExe::load_records_from_table(const char *relation_name)
{
    return RC::SUCCESS;
}

RC SelectExe::load_records_and_schames(const Selects select)
{
    for (int i = select.relation_num - 1; i >= 0; i--)
    {
        std::vector<char *> table_records;
        Table *table = datebase->find_table(select.relations[i]);
        //LOG_INFO("table find");
        table->scan_record_string(this->trx, table_records);
        //LOG_INFO("table findok ");
        add_schameInfo_into_map(select.relations[i]);
        tables_records.push_back(table_records);
    }
    return RC::SUCCESS;
}

RC SelectExe::terminal_select(std::vector<std::vector<void *>> &select_ress, std::vector<AttrType> &type, std::vector<std::string> &select_res_fields)
{
    this->select_ress = &select_ress;
    this->terminal_type = &type;
    this->terminal_fields = &select_res_fields;

    RC rc = RC::SUCCESS;
    rc = check_select(*select);
    if (rc != SUCCESS)
    {
        return rc;
    }
    rc = load_records_and_schames(*select);
    if (rc != SUCCESS)
    {
        return rc;
    }
    //show_schame_map();

    if (select->join_num_max == 0)
    {
        rc = combain_table(1, 0);
    }
    else
    {
        for (int i = 0; i < select->join_num_max; i++)
        {
            std::vector<char *> table_records;
            Table *table = datebase->find_table(select->join_on[i].relation_name);
            table->scan_record_string(this->trx, table_records);
            rc = add_schameInfo_into_map(select->join_on[i].relation_name);
            if (rc != SUCCESS)
            {
                return rc;
            }
            //show_schame_map();
            tables_records.push_back(table_records);
            rc = combain_table(0, i);
            if (rc != SUCCESS)
            {
                return rc;
            }
        }

        std::vector<char *>::iterator itr = tables_records[0].begin();
        while (itr != tables_records[0].end())
        {
            bool is_ok = true;
            for (int c_i = 0; c_i < select->condition_num; c_i++)
            {
                //LOG_INFO("%d", *(int *)*itr);
                rc = condition_filter(is_ok, select->conditions[c_i], *itr);
                if (rc != RC::SUCCESS)
                {
                    return rc;
                }
                if (!is_ok)
                {
                    //free(*itr);
                    tables_records[0].erase(itr);
                    break;
                }
            }
            if (is_ok)
                itr++;
        }
    }
    if (rc != RC::SUCCESS)
        return rc;
    vec_records = tables_records[0];

    do_order_by(vec_records);

    do_group_by(vec_records);

    //LOG_INFO("prepare res");

    rc = calculate_result();
    if (rc != SUCCESS)
    {
        return rc;
    }
    if (tables_records.size() > 1)
        free_vector(vec_records);

    load_terminal_fields();

    return rc;
}

RC select_value_compare(void *left_value, void *right_value, AttrType attr_left, AttrType attr_right, int &compare_res)
{
    AttrType tmp_attr = UNDEFINED;
    if (attr_left != attr_right)
    {
        if ((attr_left == CHARS && attr_right == DATES) || (attr_right == CHARS && attr_left == DATES))
        {
            tmp_attr = DATES;
        }
        else if ((attr_left == INTS && attr_right == FLOATS) || (attr_left == FLOATS && attr_right == INTS))
        {
            tmp_attr = FLOATS;
        }
        else
        {
            return RC::INVALID_ARGUMENT;
        }
    }
    else
    {
        tmp_attr = attr_left;
    }

    switch (tmp_attr)
    {
    case DATES:
    {
        int left = 0, right = 0;
        if (attr_left == CHARS)
        {
            if (!check_trans::check_date((char *)left_value))
                return RC::INVALID_ARGUMENT;
            left = check_trans::date_to_num(left_value);
        }
        else
        {
            left = *(int *)left_value;
        }

        if (attr_right == CHARS)
        {
            if (!check_trans::check_date((char *)right_value))
                return RC::INVALID_ARGUMENT;
            right = check_trans::date_to_num(right_value);
        }
        else
        {
            right = *(int *)right_value;
        }
        //LOG_INFO("%d %d doint date cmp", left, right);
        compare_res = left - right;
    }
    break;
    case CHARS:
    {
        compare_res = strcmp((char *)left_value, (char *)right_value);
    }
    break;
    case INTS:
    {
        int left = *(int *)left_value;
        int right = *(int *)right_value;
        ////LOG_INFO("%d %d",left,right);
        compare_res = left - right;
    }
    break;
    case FLOATS:
    {

        float left = attr_left == INTS ? (float)(*(int *)left_value) : *(float *)left_value;
        float right = attr_right == INTS ? (float)(*(int *)right_value) : *(float *)right_value;
        compare_res = (int)((left - right == 0) ? 0 : (left - right > 0 ? 1 : -1));
    }
    break;
    default:
        break;
    }
    return RC::SUCCESS;
}

RC SelectExe::condition_filter(bool &is_ok, Condition_Composite *condition, char *data_res)
{
    RC rc = RC::SUCCESS;
    std::vector<void *> left, right;
    AttrType left_attr, right_attr;
    std::vector<std::vector<void *>> select_res_left, select_res_right;
    bool type_ok = true;
    tmp_char_date = data_res;
    if (condition->left != nullptr)
        calculate_con_expression(left, condition->left, left_attr, data_res);
    if (condition->right != nullptr)
        calculate_con_expression(right, condition->right, right_attr, data_res);
    if (condition->select_attr_left != nullptr)
    {

        const Selects *selects = (Selects *)condition->select_attr_left;
        SelectExe sel_exe = SelectExe(this);
        sel_exe.SelectExe_init(this->datebase, *selects, this->trx);
        std::vector<AttrType> condition_select_attrs;
        std::vector<std::string> condition_select_fields;

        rc = sel_exe.terminal_select(select_res_left, condition_select_attrs, condition_select_fields);

        if (rc != RC::SUCCESS)
        {
            type_ok = false;
        }
        else
        {
            if (condition_select_attrs.size() > 0)
            {
                left_attr = condition_select_attrs[0];
            }
            else
            {
                left_attr = EMPTY_TYPE;
            }
            if (left_attr == UNDEFINED || select_res_left.size() > 1)
            {
                type_ok = false;
                for (size_t i = 0; i < select_res_left.size(); i++)
                {
                    free_vector(select_res_left[i]);
                }
                select_res_left.clear();
            }
            else
            {
                if (select_res_left.size() > 0)
                {
                    for (size_t i = 0; i < select_res_left[0].size(); i++)
                    {
                        left.push_back(select_res_left[0][i]);
                    }
                }
            }
        }
    }
    if (!type_ok)
    {
        free_vector(left);
        free_vector(right);
        return RC::INVALID_ARGUMENT;
    }
    if (condition->select_attr_right != nullptr)
    {

        const Selects *selects = (Selects *)condition->select_attr_right;
        SelectExe sel_exe = SelectExe(this);
        sel_exe.SelectExe_init(this->datebase, *selects, this->trx);
        std::vector<AttrType> condition_select_attrs;
        std::vector<std::string> condition_select_fields;

        rc = sel_exe.terminal_select(select_res_right, condition_select_attrs, condition_select_fields);

        //LOG_INFO("right select ok? %d", rc);
        if (rc != RC::SUCCESS)
        {
            type_ok = false;
        }
        else
        {
            if (condition_select_attrs.size() > 0)
            {
                right_attr = condition_select_attrs[0];
            }
            else
            {
                right_attr = EMPTY_TYPE;
            }

            if (right_attr == UNDEFINED || select_res_right.size() > 1)
            {
                type_ok = false;
                for (size_t i = 0; i < select_res_right.size(); i++)
                {
                    free_vector(select_res_right[i]);
                }
                select_res_right.clear();
            }
            else
            {
                if (select_res_right.size() > 0)
                {
                    for (size_t i = 0; i < select_res_right[0].size(); i++)
                    {
                        right.push_back(select_res_right[0][i]);
                    }
                }
            }
        }
    }

    if (!type_ok)
    {
        free_vector(left);
        free_vector(right);
        return RC::INVALID_ARGUMENT;
    }
    //LOG_INFO("Type %d %d %d", left_attr, right_attr, type_ok);

    //check left_res can do with right_res
    if (left_attr != right_attr && left_attr != EMPTY_TYPE && right_attr != EMPTY_TYPE)
    {
        if (!((left_attr == NULL_TYPE || right_attr == NULL_TYPE) || (left_attr == INTS && right_attr == FLOATS) || (left_attr == FLOATS && right_attr == INTS) || (left_attr == DATES && right_attr == CHARS) || (left_attr == CHARS && right_attr == DATES)))
        {
            type_ok = false;
        }
    }

    if (!type_ok)
    {
        free_vector(left);
        free_vector(right);
        return RC::INVALID_ARGUMENT;
    }

    int cmp_result = -1;

    if (condition->comp == ATTR_IN || condition->comp == ATTR_NOT_IN)
    {
        if (condition->comp == ATTR_IN)
        {
            if (right_attr == EMPTY_TYPE || left_attr == EMPTY_TYPE)
            {
                is_ok = false;
            }
            else
            {
                is_ok = false;
                for (auto it : right)
                {

                    rc = select_value_compare(left[0], it, left_attr, right_attr, cmp_result);
                    if (cmp_result == 0)
                    {
                        is_ok = true;
                        break;
                    }
                }
            }
        }
        else
        {
            is_ok = true;
            for (auto it : right)
            {
                rc = select_value_compare(left[0], it, left_attr, right_attr, cmp_result);
                if (cmp_result == 0)
                {
                    is_ok = false;
                    break;
                }
            }
        }
    }
    else
    {
        if (left.empty() || right.empty() || left_attr == EMPTY_TYPE || right_attr == EMPTY_TYPE)
        {
            is_ok = false;
        }
        else
        {
            if (left.size() > 1 || right.size() > 1)
                rc = RC::INVALID_ARGUMENT;
            if (rc != RC::SUCCESS)
                return rc;

            if (left_attr == NULL_TYPE || right_attr == NULL_TYPE)
            {
                if (condition->comp == ATTR_IS)
                {
                    is_ok = left_attr == right_attr ? true : false;
                }
                else if (condition->comp == ATTR_IS_NOT)
                {
                    is_ok = left_attr == right_attr ? false : true;
                }
                else
                {
                    is_ok = false;
                }
            }
            else
            {

                rc = select_value_compare(left[0], right[0], left_attr, right_attr, cmp_result);
                ////LOG_INFO("%d cmp_Res %d", condition->comp, cmp_result);
                switch (condition->comp)
                {
                case EQUAL_TO:
                {
                    if (0 == cmp_result)
                    {
                        is_ok = true;
                    }
                    else
                    {
                        is_ok = false;
                    }
                }
                break;
                case LESS_EQUAL:
                {
                    if (cmp_result <= 0)
                    {
                        is_ok = true;
                    }
                    else
                    {
                        is_ok = false;
                    }
                }
                break;
                case NOT_EQUAL:
                {
                    if (cmp_result != 0)
                    {
                        is_ok = true;
                    }
                    else
                    {
                        is_ok = false;
                    }
                }
                break;
                case LESS_THAN:
                {
                    if (cmp_result < 0)
                    {
                        is_ok = true;
                    }
                    else
                    {
                        is_ok = false;
                    }
                }
                break;
                case GREAT_EQUAL:
                {
                    if (cmp_result >= 0)
                    {
                        is_ok = true;
                    }
                    else
                    {
                        is_ok = false;
                    }
                }
                break;
                case GREAT_THAN:
                {
                    if (cmp_result > 0)
                    {
                        is_ok = true;
                    }
                    else
                    {
                        is_ok = false;
                    }
                }
                break;
                default:
                    break;
                }
            }
        }
    }

    //LOG_INFO("free left_right_con_expression");
    free_vector(left);
    free_vector(right);
    //LOG_INFO("free left_right_con_expression okkk %d", rc);
    return rc;
}

RC SelectExe::combain(char *data_res, int table_num, int is_select, int join_num, int tmp_len)
{
    RC rc = RC::SUCCESS;
    for (size_t i = 0; i < tables_records[table_num].size(); i++)
    {
        memcpy(data_res + tmp_len, tables_records[table_num][i], table_record_length[table_num] * sizeof(char));

        if (table_num == tables_records.size() - 1)
        {
            bool is_ok = true;
            if (is_select)
            {
                for (int c_i = 0; c_i < select->condition_num; c_i++)
                {
                    rc = condition_filter(is_ok, select->conditions[c_i], data_res);
                    if (rc != RC::SUCCESS)
                    {
                        return rc;
                    }
                    if (!is_ok)
                        break;
                }
            }
            else
            {
                ////LOG_INFO(" is sel %d con_num %d",is_select, (int)select->join_on[join_num].condition_num);
                for (int c_i = 0; c_i < select->join_on[join_num].condition_num; c_i++)
                {
                    rc = condition_filter(is_ok, select->join_on[join_num].conditions[c_i], data_res);
                    if (rc != RC::SUCCESS)
                    {
                        return rc;
                    }
                    if (!is_ok)
                        break;
                }
            }
            if (is_ok)
            {
                ////LOG_INFO(" isokkkkkkkkkkkkkkkkkk");
                char *tmp_res = (char *)malloc(tmp_total_len * sizeof(char));
                memcpy(tmp_res, data_res, tmp_total_len * sizeof(char));
                middle_records.push_back(tmp_res);
            }
        }
        else
        {
            rc = combain(data_res, table_num + 1, is_select, join_num, tmp_len + table_record_length[table_num]);
            if (rc != RC::SUCCESS)
                return rc;
        }
    }
    return rc;
}

RC SelectExe::combain_table(int is_select, int join_num)
{
    RC rc = RC::SUCCESS;
    tmp_total_len = 0;
    for (auto it : table_record_length)
    {
        tmp_total_len += it;
    }
    char data_res[tmp_total_len];

    rc = combain(data_res, 0, is_select, join_num, 0);
    table_record_length.clear();
    table_record_length.push_back(tmp_total_len);
    if (rc != RC::SUCCESS)
    {
        return rc;
    }

    if (combain_deep > 0)
    {
        //LOG_INFO("free middle tables_records %d", (int)tables_records[0].size());
        free_vector(tables_records[0]);
    }
    combain_deep++;
    tables_records.clear();
    tables_records.push_back(middle_records);
    middle_records.clear();
    //LOG_INFO("record %d", (int)tables_records[0].size());
    //show_records();
    return rc;
}
void SelectExe::show_schame_map()
{
    for (auto it : table_map)
    {
        //LOG_INFO("name=%s type=%d offset=%d len=%d", it.first.c_str(), it.second.type, it.second.offset, it.second.len);
    }
}
RC SelectExe::show_records()
{

    for (auto record : tables_records[0])
    {
        //LOG_INFO("record :");
        for (auto it : table_map)
        {
            //LOG_INFO("%s", it.first.c_str());
            switch (it.second.type)
            {
            case INTS:
                //LOG_INFO("%d", *(int *)((char *)record + it.second.offset));
                break;

            case FLOATS:
                //LOG_INFO("%f", *(float *)((char *)record + it.second.offset));
                break;

            case CHARS:
                //LOG_INFO("%s", (char *)((char *)record + it.second.offset));
                break;

            case DATES:
                //LOG_INFO("%d", *(int *)((char *)record + it.second.offset));
                break;

            default:
                break;
            }
        }
    }

    return RC::SUCCESS;
}
RC SelectExe::SelectExe_init(Db *datebase, const Selects &selects, Trx *trx)
{ //形参是引用，实参是对象
    this->datebase = datebase;
    this->select = &selects;
    this->trx = trx;
    return RC::SUCCESS;
}
