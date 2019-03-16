//
// Created by Khyber on 3/16/2019.
//

#pragma once

#include "src/share/common/debug.h"

#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/BasicBlock.h"

namespace llvm {
    
    raw_ostream& operator<<(raw_ostream& out, bool boolean) {
        return out << (boolean ? "true" : "false");
    }
    
    raw_ostream& operator<<(raw_ostream& out, std::string_view view) {
        return out << StringRef(view.data(), view.size());
    }
    
    std::string_view to_string_view(Type::TypeID typeId) {
        switch (typeId) {
            case Type::VoidTyID:
                return "void";
            case Type::HalfTyID:
                return "half";
            case Type::FloatTyID:
                return "float";
            case Type::DoubleTyID:
                return "double";
            case Type::X86_FP80TyID:
                return "x86_fp80";
            case Type::FP128TyID:
                return "fp128";
            case Type::PPC_FP128TyID:
                return "ppc_fp128";
            case Type::LabelTyID:
                return "label";
            case Type::MetadataTyID:
                return "metadata";
            case Type::X86_MMXTyID:
                return "x86_mmx";
            case Type::TokenTyID:
                return "token";
            case Type::IntegerTyID:
                return "integer";
            
            
            case Type::FunctionTyID:
                return "function";
            case Type::StructTyID:
                return "struct";
            case Type::PointerTyID:
                return "pointer";
            case Type::ArrayTyID:
                return "array";
            case Type::VectorTyID:
                return "vector";
        }
        auto invalid = "Invalid TypeID (" + std::to_string(static_cast<size_t>(typeId)) + ")";
        llvm_unreachable(invalid.c_str());
    }
    
    raw_ostream& operator<<(raw_ostream& out, Type::TypeID typeId) {
        return out << to_string_view(typeId);
    }
    
    std::string uuid(BasicBlock& block) {
        std::string s;
        raw_string_ostream out(s);
        block.printAsOperand(out, false);
        return out.str();
    }
    
}

#define llvm_debug() _debug(llvm::errs())

#define llvm_dbg(expr) llvm_debug()(_expr(expr))
