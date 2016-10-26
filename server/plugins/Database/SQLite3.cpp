//
// SQLite3.cpp for server in /home/galibe_s/project/SpiderServer/plugins/Database
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Aug 20 10:36:29 2016 stephane galibert
// Last update Wed Oct 26 11:53:21 2016 stephane galibert
//

#include "SQLite3.hpp"

int callback(void *data, int ac, char **av, char **azColName)
{
  (void)data;
  for (int i = 0 ; i < ac ; ++i) {
    std::clog << azColName[i] << ": " << ((av[i]) ? av[i] : "NULL") << std::endl;
  }
  return (0);
}

SQLite3::SQLite3(CRString path)
  : _path(path)
{
  _db = NULL;
}

SQLite3::~SQLite3(void)
{
}

void SQLite3::createTable(CRString table)
{
  try {
    open();
    exec(table, NULL);
  } catch (std::runtime_error const& e) {
    throw (e);
  }
}

void SQLite3::close(void)
{
  if (_db) {
    sqlite3_close(_db);
  }
}

void SQLite3::insert(CRString table, CRString colName, CRString value)
{
  std::string query;

  query += "INSERT INTO " + table + "(" + colName + ") ";
  query += "VALUES ('" + value + "');";
  try {
    exec(query, NULL);
  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
  }
}

void SQLite3::select(CRString table, CRString id, CRString idValue)
{
  std::string query;

  query = "SELECT * FROM " + table + " WHERE " + id + "='" + idValue + "';";
  try {
    exec(query, &callback);
  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
  }
}

void SQLite3::update(CRString table, CRString colName, CRString nValue,
		     CRString id, CRString idValue)
{
  std::string query;
  query += "UPDATE " + table + " SET " + colName + " = '" + nValue + "' ";
  query += "WHERE " + id + "='" + idValue + "';";
  try {
    exec(query, NULL);
  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
  }
}

void SQLite3::erase(CRString table, CRString id, CRString idValue)
{
  std::string query;
  query += "DELETE from " + table;
  query += " WHERE " + id + "='" + idValue + "';";
  try {
    exec(query, NULL);
  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
  }
}

bool SQLite3::exist(CRString table, CRString colName, CRString value)
{
  std::string q;
  sqlite3_stmt *stmt = NULL;
  bool ret = false;

  q += "SELECT * FROM " + table + " WHERE " + colName + " = '" + value + "';";
  if (sqlite3_prepare(_db, q.c_str(), q.size() + 1, &stmt, NULL) != SQLITE_OK) {
    std::cerr << "can't prepare SQL statement in SQLite3::exist" << std::endl;
    return (false);
  }
  ret = sqlite3_step(stmt) == SQLITE_ROW;
  sqlite3_finalize(stmt);
  return (ret);
}

std::string SQLite3::execute(CRString q)
{
  std::ostringstream buf;
  boost::property_tree::ptree root, nodeObject;
  sqlite3_stmt *stmt = NULL;

  if (sqlite3_prepare(_db, q.c_str(), q.size() + 1, &stmt, NULL) != SQLITE_OK) {
    JSONBuilder builder;
    builder.addValue("type", "error");
    builder.addValue("name", "can't prepare this SQL statement");
    return (builder.get());
  }
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    const char *colName = NULL;
    boost::property_tree::ptree nodeData;
    for (int i = 0 ; (colName = sqlite3_column_name(stmt, i)) ; ++i) {
      std::string data = reinterpret_cast<const char *>(sqlite3_column_text(stmt, i));
      nodeData.put(colName, data);
    }
    const char *id = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    nodeObject.push_back(std::make_pair(id, nodeData));
  }
  root.put("type", "result");
  root.put_child("data", nodeObject);
  boost::property_tree::write_json(buf, root, false);
  sqlite3_finalize(stmt);
  return (buf.str());
}

void SQLite3::open(void)
{
  if (sqlite3_open(_path.c_str(), &_db) != SQLITE_OK) {
    throw (std::runtime_error("Error on opening '" + _path + "'"));
  }
}

void SQLite3::exec(CRString query, int (*callback)(void *, int, char **, char **))
{
  char *err = NULL;

  if (sqlite3_exec(_db, query.c_str(), callback, NULL, &err) != SQLITE_OK) {
    std::string tmp(err);
    sqlite3_free(err);
    throw (std::runtime_error("Error DB: " + tmp));
  }
}
