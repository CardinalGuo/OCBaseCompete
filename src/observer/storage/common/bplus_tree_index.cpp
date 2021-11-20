/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by wangyunlai.wyl on 2021/5/19.
//

#include "storage/common/bplus_tree_index.h"
#include "common/log/log.h"

BplusTreeIndex::~BplusTreeIndex() noexcept {
  close();
}


RC BplusTreeIndex::create(const char *file_name, const IndexMeta &index_meta, const FieldMeta &field_meta) {
  if (inited_) {
    return RC::RECORD_OPENNED;
  }

  RC rc = Index::init(index_meta, field_meta);
  if (rc != RC::SUCCESS) {
    return rc;
  }

///////////////////////20211118
  rc = index_handler_.create(file_name, field_meta.type(), field_meta.len(), index_meta.is_unique());
  if (RC::SUCCESS == rc) {
    inited_ = true;
  }
  return rc;
}

RC BplusTreeIndex::create(const char *file_name, const IndexMeta &index_meta, std::vector<FieldMeta> field_vec) {
  if (inited_) {
    return RC::RECORD_OPENNED;
  }

  RC rc = Index::init(index_meta, field_vec, index_meta_.is_unique());
  if (rc != RC::SUCCESS) {
    return rc;
  }

  AttrType attr_types[8];
  int attr_lengths[8];
  int field_num = (int)field_vec.size();
  for (int i = 0;i < field_num;i++){
    attr_lengths[i] = field_vec[i].len();
    attr_types[i] = field_vec[i].type();
  }
///////////////////////20211118
  rc = index_handler_.create(file_name, attr_types, attr_lengths, index_meta.is_unique(), field_num);
  if (RC::SUCCESS == rc) {
    inited_ = true;
  }
  return rc;
}

RC BplusTreeIndex::open(const char *file_name, const IndexMeta &index_meta, std::vector<FieldMeta> &field_meta_vec, const int is_unique) {
  if (inited_) {
    return RC::RECORD_OPENNED;
  }
  RC rc = Index::init(index_meta, field_meta_vec, is_unique);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = index_handler_.open(file_name);
  if (RC::SUCCESS == rc) {
    inited_ = true;
  }
  return rc;
}

RC BplusTreeIndex::open(const char *file_name, const IndexMeta &index_meta, const FieldMeta &field_meta) {
  if (inited_) {
    return RC::RECORD_OPENNED;
  }
  RC rc = Index::init(index_meta, field_meta);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = index_handler_.open(file_name);
  if (RC::SUCCESS == rc) {
    inited_ = true;
  }
  return rc;
}

RC BplusTreeIndex::close() {
  if (inited_) {
    index_handler_.close();
    inited_ = false;
  }
  return RC::SUCCESS;
}

RC BplusTreeIndex::insert_entry(const char *record, const RID *rid) {
  char *record_key;
  int sum_size = 0;
  for (auto it : field_meta_vec_){
    sum_size += it.len();
  }
  record_key = (char *)malloc(sum_size * sizeof(char));
  sum_size = 0;
  for (auto it : field_meta_vec_){
    LOG_INFO("%d %d %d %d", it.type(), it.offset(), it.len(), *(int *)(record + it.offset()));
    memcpy(record_key + sum_size, record + it.offset(), it.len());
    sum_size += it.len();
  }
  return index_handler_.insert_entry(record_key, rid);
}

RC BplusTreeIndex::delete_entry(const char *record, const RID *rid) {
  char *record_key;
  int sum_size = 0;
  for (auto it : field_meta_vec_){
    sum_size += it.len();
  }
  record_key = (char *)malloc(sum_size * sizeof(char));
  sum_size = 0;
  for (auto it : field_meta_vec_){
    memcpy(record_key + sum_size, record + it.offset(), it.len());
    sum_size += it.len();
  }
  return index_handler_.delete_entry(record_key, rid);
}

IndexScanner *BplusTreeIndex::create_scanner(CompOp comp_op, const char *value) {
  BplusTreeScanner *bplus_tree_scanner = new BplusTreeScanner(index_handler_);
  RC rc = bplus_tree_scanner->open(comp_op, value);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open index scanner. rc=%d:%s", rc, strrc(rc));
    delete bplus_tree_scanner;
    return nullptr;
  }

  BplusTreeIndexScanner *index_scanner = new BplusTreeIndexScanner(bplus_tree_scanner);
  return index_scanner;
}

RC BplusTreeIndex::sync() {
  return index_handler_.sync();
}

////////////////////////////////////////////////////////////////////////////////
BplusTreeIndexScanner::BplusTreeIndexScanner(BplusTreeScanner *tree_scanner) :
    tree_scanner_(tree_scanner) {
}

BplusTreeIndexScanner::~BplusTreeIndexScanner() noexcept {
  tree_scanner_->close();
  delete tree_scanner_;
}

RC BplusTreeIndexScanner::next_entry(RID *rid) {
  return tree_scanner_->next_entry(rid);
}

RC BplusTreeIndexScanner::destroy() {
  delete this;
  return RC::SUCCESS;
}