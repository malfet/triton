#ifndef TDL_INCLUDE_IR_VALUE_H
#define TDL_INCLUDE_IR_VALUE_H

#include <string>
#include <vector>
#include <memory>
#include <set>

namespace tdl{
namespace ir{

class type;
class use;
class user;

//===----------------------------------------------------------------------===//
//                               value class
//===----------------------------------------------------------------------===//

class value {
public:
  // constructor
  value(type *ty, const std::string &name = "");
  virtual ~value(){ }
  // uses
  void add_use(user* arg);
  unsigned erase_use(user* arg);
  const std::set<user*> &get_users() { return users_; }
  virtual void replace_all_uses_with(value *target);
  // name
  void set_name(const std::string &name);
  const std::string &get_name() const { return name_; }
  type* get_type() const { return ty_; }

private:
  type *ty_;
  std::string name_;

protected:
  std::set<user*> users_;
};

//===----------------------------------------------------------------------===//
//                               user class
//===----------------------------------------------------------------------===//

class user: public value{
public:
  typedef std::vector<value*>      ops_t;
  typedef ops_t::iterator       op_iterator;
  typedef ops_t::const_iterator const_op_iterator;

protected:
  void resize_ops(unsigned n) { ops_.resize(n); }

public:
  // Constructor
  user(type *ty, unsigned num_ops, const std::string &name = "")
      : value(ty, name), ops_(num_ops){ }

  // Operands
  const ops_t& ops() { return ops_; }
  op_iterator op_begin() { return ops_.begin(); }
  op_iterator op_end()   { return ops_.end(); }
  void     set_operand(unsigned i, value *x);
  value   *get_operand(unsigned i);
  unsigned get_num_operands() const ;

  // Utils
  void replace_all_uses_with(value *target);
  void replace_uses_of_with(value *before, value *after);

private:
  ops_t ops_;
};

}
}

#endif
