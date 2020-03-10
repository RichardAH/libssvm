//===-- ssvm/validator/validator.h - Loader flow control class definition--===//
//
// Part of the SSVM Project.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the validator class, which controls
/// flow of WASM validation.
///
//===----------------------------------------------------------------------===//
#pragma once

#include "common/ast/module.h"

#include <deque>
#include <map>
#include <string>

namespace SSVM {
namespace Validator {

namespace {
using OpCode = AST::Instruction::OpCode;
} // namespace

enum class ErrCode : unsigned int { Success = 0, Invalid };

enum class Value : unsigned int { Unknown, I32, I64, F32, F64 };

struct CtrlFrame {
  std::vector<Value> LabelTypes;
  std::vector<Value> EndTypes;
  size_t Height;
  bool IsUnreachable;
};

class ValidateMachine {
  void runOp(AST::Instruction *);
  void push_opd(Value);
  Value pop_opd();
  Value pop_opd(Value);
  void pop_opds(const std::vector<Value> &);
  void push_opds(const std::vector<Value> &);
  void push_ctrl(const std::vector<Value> &, const std::vector<Value> &);
  std::vector<Value> pop_ctrl();
  void unreachable();

  Value getLocal(unsigned int);
  void setLocal(unsigned int, Value);
  Value getGlobal(unsigned int);
  void setGlobal(unsigned int, Value);
  ErrCode validateWarp(const AST::InstrVec &);

public:
  void addLocal(unsigned int, ValType);
  void addGlobal(AST::GlobalType);
  void addFunc(AST::FunctionType *);
  void addType(AST::FunctionType *);
  void reset(bool CleanGlobal = false);
  void init();
  ErrCode validate(const AST::InstrVec &, const std::vector<ValType> &);

  std::deque<Value> result() { return ValStack; };
  auto &getGlobals() { return Global; }
  auto &getFunctions() { return Funcs; }
  auto &getTypes() { return Types; }

private:
  std::map<unsigned int, Value> Local;
  std::deque<Value> ValStack;
  std::deque<CtrlFrame> CtrlStack;
  std::vector<Value> ReturnVals;

  std::vector<AST::GlobalType> Global;
  std::vector<std::pair<std::vector<Value>, std::vector<Value>>> Funcs;
  std::vector<std::pair<std::vector<Value>, std::vector<Value>>> Types;

  static const size_t NAT = -1;
};

/// Loader flow control class.
class Validator {
  /// Sec. valid types
  ErrCode validate(const AST::Limit *, unsigned int);
  ErrCode validate(AST::FunctionType *);
  ErrCode validate(AST::TableType *);
  ErrCode validate(AST::MemoryType *);
  ErrCode validate(AST::GlobalType *);

  /// Sec. Instructions types
  ErrCode validate(AST::FunctionSection *, AST::CodeSection *,
                   AST::TypeSection *);
  ErrCode validate(AST::CodeSegment *, AST::FunctionType *);
  ErrCode validate(AST::MemorySection *);
  ErrCode validate(AST::TableSection *);
  ErrCode validate(AST::GlobalSection *);
  ErrCode validate(AST::GlobalSegment *);
  ErrCode validate(AST::ElementSection *);
  ErrCode validate(AST::ElementSegment *);
  ErrCode validate(AST::StartSection *);
  ErrCode validate(AST::ExportSection *);
  ErrCode validate(AST::ExportDesc *);
  ErrCode validate(AST::ImportSection *, AST::TypeSection *);
  ErrCode validate(AST::ImportDesc *, AST::TypeSection *);

  /// Validator Stack Operation
public:
  Validator() = default;
  ~Validator() = default;

  /// Validate AST::Module.
  ErrCode validate(std::unique_ptr<AST::Module> &);
  void reset();

private:
  ValidateMachine VM;

  static const unsigned int LIMIT_TABLETYPE = UINT32_MAX; // 2^32-1
  static const unsigned int LIMIT_MEMORYTYPE = 1U << 16;
};

} // namespace Validator
} // namespace SSVM