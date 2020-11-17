#include "src/ast/ast.h"
#include "src/builtins/builtins-array-gen.h"
#include "src/builtins/builtins-bigint-gen.h"
#include "src/builtins/builtins-collections-gen.h"
#include "src/builtins/builtins-constructor-gen.h"
#include "src/builtins/builtins-data-view-gen.h"
#include "src/builtins/builtins-iterator-gen.h"
#include "src/builtins/builtins-promise-gen.h"
#include "src/builtins/builtins-promise.h"
#include "src/builtins/builtins-proxy-gen.h"
#include "src/builtins/builtins-regexp-gen.h"
#include "src/builtins/builtins-string-gen.h"
#include "src/builtins/builtins-typed-array-gen.h"
#include "src/builtins/builtins-utils-gen.h"
#include "src/builtins/builtins-wasm-gen.h"
#include "src/builtins/builtins.h"
#include "src/codegen/code-factory.h"
#include "src/heap/factory-inl.h"
#include "src/ic/binary-op-assembler.h"
#include "src/objects/arguments.h"
#include "src/objects/bigint.h"
#include "src/objects/elements-kind.h"
#include "src/objects/free-space.h"
#include "src/objects/js-function.h"
#include "src/objects/js-generator.h"
#include "src/objects/js-objects.h"
#include "src/objects/js-promise.h"
#include "src/objects/js-regexp-string-iterator.h"
#include "src/objects/js-weak-refs.h"
#include "src/objects/objects.h"
#include "src/objects/ordered-hash-table.h"
#include "src/objects/property-array.h"
#include "src/objects/property-descriptor-object.h"
#include "src/objects/source-text-module.h"
#include "src/objects/stack-frame-info.h"
#include "src/objects/synthetic-module.h"
#include "src/objects/template-objects.h"
#include "src/torque/runtime-support.h"
#include "torque-generated/src/builtins/aggregate-error-tq-csa.h"
#include "torque-generated/src/builtins/array-copywithin-tq-csa.h"
#include "torque-generated/src/builtins/array-every-tq-csa.h"
#include "torque-generated/src/builtins/array-filter-tq-csa.h"
#include "torque-generated/src/builtins/array-find-tq-csa.h"
#include "torque-generated/src/builtins/array-findindex-tq-csa.h"
#include "torque-generated/src/builtins/array-foreach-tq-csa.h"
#include "torque-generated/src/builtins/array-from-tq-csa.h"
#include "torque-generated/src/builtins/array-isarray-tq-csa.h"
#include "torque-generated/src/builtins/array-join-tq-csa.h"
#include "torque-generated/src/builtins/array-lastindexof-tq-csa.h"
#include "torque-generated/src/builtins/array-map-tq-csa.h"
#include "torque-generated/src/builtins/array-of-tq-csa.h"
#include "torque-generated/src/builtins/array-reduce-right-tq-csa.h"
#include "torque-generated/src/builtins/array-reduce-tq-csa.h"
#include "torque-generated/src/builtins/array-reverse-tq-csa.h"
#include "torque-generated/src/builtins/array-shift-tq-csa.h"
#include "torque-generated/src/builtins/array-slice-tq-csa.h"
#include "torque-generated/src/builtins/array-some-tq-csa.h"
#include "torque-generated/src/builtins/array-splice-tq-csa.h"
#include "torque-generated/src/builtins/array-unshift-tq-csa.h"
#include "torque-generated/src/builtins/array-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/bigint-tq-csa.h"
#include "torque-generated/src/builtins/boolean-tq-csa.h"
#include "torque-generated/src/builtins/builtins-string-tq-csa.h"
#include "torque-generated/src/builtins/cast-tq-csa.h"
#include "torque-generated/src/builtins/collections-tq-csa.h"
#include "torque-generated/src/builtins/constructor-tq-csa.h"
#include "torque-generated/src/builtins/conversion-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/console-tq-csa.h"
#include "torque-generated/src/builtins/data-view-tq-csa.h"
#include "torque-generated/src/builtins/finalization-registry-tq-csa.h"
#include "torque-generated/src/builtins/frames-tq-csa.h"
#include "torque-generated/src/builtins/frame-arguments-tq-csa.h"
#include "torque-generated/src/builtins/function-tq-csa.h"
#include "torque-generated/src/builtins/growable-fixed-array-tq-csa.h"
#include "torque-generated/src/builtins/ic-callable-tq-csa.h"
#include "torque-generated/src/builtins/ic-tq-csa.h"
#include "torque-generated/src/builtins/internal-coverage-tq-csa.h"
#include "torque-generated/src/builtins/internal-tq-csa.h"
#include "torque-generated/src/builtins/iterator-tq-csa.h"
#include "torque-generated/src/builtins/math-tq-csa.h"
#include "torque-generated/src/builtins/number-tq-csa.h"
#include "torque-generated/src/builtins/object-fromentries-tq-csa.h"
#include "torque-generated/src/builtins/object-tq-csa.h"
#include "torque-generated/src/builtins/promise-abstract-operations-tq-csa.h"
#include "torque-generated/src/builtins/promise-all-tq-csa.h"
#include "torque-generated/src/builtins/promise-all-element-closure-tq-csa.h"
#include "torque-generated/src/builtins/promise-any-tq-csa.h"
#include "torque-generated/src/builtins/promise-constructor-tq-csa.h"
#include "torque-generated/src/builtins/promise-finally-tq-csa.h"
#include "torque-generated/src/builtins/promise-misc-tq-csa.h"
#include "torque-generated/src/builtins/promise-race-tq-csa.h"
#include "torque-generated/src/builtins/promise-reaction-job-tq-csa.h"
#include "torque-generated/src/builtins/promise-resolve-tq-csa.h"
#include "torque-generated/src/builtins/promise-then-tq-csa.h"
#include "torque-generated/src/builtins/promise-jobs-tq-csa.h"
#include "torque-generated/src/builtins/proxy-constructor-tq-csa.h"
#include "torque-generated/src/builtins/proxy-delete-property-tq-csa.h"
#include "torque-generated/src/builtins/proxy-get-property-tq-csa.h"
#include "torque-generated/src/builtins/proxy-get-prototype-of-tq-csa.h"
#include "torque-generated/src/builtins/proxy-has-property-tq-csa.h"
#include "torque-generated/src/builtins/proxy-is-extensible-tq-csa.h"
#include "torque-generated/src/builtins/proxy-prevent-extensions-tq-csa.h"
#include "torque-generated/src/builtins/proxy-revocable-tq-csa.h"
#include "torque-generated/src/builtins/proxy-revoke-tq-csa.h"
#include "torque-generated/src/builtins/proxy-set-property-tq-csa.h"
#include "torque-generated/src/builtins/proxy-set-prototype-of-tq-csa.h"
#include "torque-generated/src/builtins/proxy-tq-csa.h"
#include "torque-generated/src/builtins/reflect-tq-csa.h"
#include "torque-generated/src/builtins/regexp-exec-tq-csa.h"
#include "torque-generated/src/builtins/regexp-match-all-tq-csa.h"
#include "torque-generated/src/builtins/regexp-match-tq-csa.h"
#include "torque-generated/src/builtins/regexp-replace-tq-csa.h"
#include "torque-generated/src/builtins/regexp-search-tq-csa.h"
#include "torque-generated/src/builtins/regexp-source-tq-csa.h"
#include "torque-generated/src/builtins/regexp-split-tq-csa.h"
#include "torque-generated/src/builtins/regexp-test-tq-csa.h"
#include "torque-generated/src/builtins/regexp-tq-csa.h"
#include "torque-generated/src/builtins/string-endswith-tq-csa.h"
#include "torque-generated/src/builtins/string-html-tq-csa.h"
#include "torque-generated/src/builtins/string-iterator-tq-csa.h"
#include "torque-generated/src/builtins/string-pad-tq-csa.h"
#include "torque-generated/src/builtins/string-repeat-tq-csa.h"
#include "torque-generated/src/builtins/string-replaceall-tq-csa.h"
#include "torque-generated/src/builtins/string-slice-tq-csa.h"
#include "torque-generated/src/builtins/string-startswith-tq-csa.h"
#include "torque-generated/src/builtins/string-substring-tq-csa.h"
#include "torque-generated/src/builtins/string-substr-tq-csa.h"
#include "torque-generated/src/builtins/symbol-tq-csa.h"
#include "torque-generated/src/builtins/torque-internal-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-createtypedarray-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-every-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-entries-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-filter-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-find-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-findindex-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-foreach-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-from-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-keys-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-of-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-reduce-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-reduceright-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-set-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-slice-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-some-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-sort-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-subarray-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-values-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-tq-csa.h"
#include "torque-generated/src/builtins/wasm-tq-csa.h"
#include "torque-generated/src/builtins/weak-ref-tq-csa.h"
#include "torque-generated/src/ic/handler-configuration-tq-csa.h"
#include "torque-generated/src/objects/allocation-site-tq-csa.h"
#include "torque-generated/src/objects/api-callbacks-tq-csa.h"
#include "torque-generated/src/objects/arguments-tq-csa.h"
#include "torque-generated/src/objects/cell-tq-csa.h"
#include "torque-generated/src/objects/code-tq-csa.h"
#include "torque-generated/src/objects/contexts-tq-csa.h"
#include "torque-generated/src/objects/data-handler-tq-csa.h"
#include "torque-generated/src/objects/debug-objects-tq-csa.h"
#include "torque-generated/src/objects/descriptor-array-tq-csa.h"
#include "torque-generated/src/objects/embedder-data-array-tq-csa.h"
#include "torque-generated/src/objects/feedback-cell-tq-csa.h"
#include "torque-generated/src/objects/feedback-vector-tq-csa.h"
#include "torque-generated/src/objects/fixed-array-tq-csa.h"
#include "torque-generated/src/objects/foreign-tq-csa.h"
#include "torque-generated/src/objects/free-space-tq-csa.h"
#include "torque-generated/src/objects/heap-number-tq-csa.h"
#include "torque-generated/src/objects/heap-object-tq-csa.h"
#include "torque-generated/src/objects/js-array-buffer-tq-csa.h"
#include "torque-generated/src/objects/js-array-tq-csa.h"
#include "torque-generated/src/objects/js-collection-iterator-tq-csa.h"
#include "torque-generated/src/objects/js-collection-tq-csa.h"
#include "torque-generated/src/objects/js-generator-tq-csa.h"
#include "torque-generated/src/objects/js-objects-tq-csa.h"
#include "torque-generated/src/objects/js-promise-tq-csa.h"
#include "torque-generated/src/objects/js-proxy-tq-csa.h"
#include "torque-generated/src/objects/js-regexp-string-iterator-tq-csa.h"
#include "torque-generated/src/objects/js-regexp-tq-csa.h"
#include "torque-generated/src/objects/js-weak-refs-tq-csa.h"
#include "torque-generated/src/objects/literal-objects-tq-csa.h"
#include "torque-generated/src/objects/map-tq-csa.h"
#include "torque-generated/src/objects/microtask-tq-csa.h"
#include "torque-generated/src/objects/module-tq-csa.h"
#include "torque-generated/src/objects/name-tq-csa.h"
#include "torque-generated/src/objects/oddball-tq-csa.h"
#include "torque-generated/src/objects/ordered-hash-table-tq-csa.h"
#include "torque-generated/src/objects/primitive-heap-object-tq-csa.h"
#include "torque-generated/src/objects/promise-tq-csa.h"
#include "torque-generated/src/objects/property-array-tq-csa.h"
#include "torque-generated/src/objects/property-cell-tq-csa.h"
#include "torque-generated/src/objects/property-descriptor-object-tq-csa.h"
#include "torque-generated/src/objects/prototype-info-tq-csa.h"
#include "torque-generated/src/objects/regexp-match-info-tq-csa.h"
#include "torque-generated/src/objects/scope-info-tq-csa.h"
#include "torque-generated/src/objects/script-tq-csa.h"
#include "torque-generated/src/objects/shared-function-info-tq-csa.h"
#include "torque-generated/src/objects/source-text-module-tq-csa.h"
#include "torque-generated/src/objects/stack-frame-info-tq-csa.h"
#include "torque-generated/src/objects/string-tq-csa.h"
#include "torque-generated/src/objects/struct-tq-csa.h"
#include "torque-generated/src/objects/synthetic-module-tq-csa.h"
#include "torque-generated/src/objects/template-objects-tq-csa.h"
#include "torque-generated/src/objects/template-tq-csa.h"
#include "torque-generated/src/wasm/wasm-objects-tq-csa.h"
#include "torque-generated/test/torque/test-torque-tq-csa.h"
#include "torque-generated/third_party/v8/builtins/array-sort-tq-csa.h"

namespace v8 {
namespace internal {

TNode<BigInt> Cast_BigIntBase_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BigInt> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = DownCastForTorqueClass_BigIntBase_0(state_, TNode<HeapObject>{p_obj}, &label1);
    ca_.Goto(&block3);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block4);
    }
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    ca_.Goto(label_CastError);
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block5);
  }

    ca_.Bind(&block5);
  return TNode<BigInt>{tmp0};
}

TNode<BigInt> Convert_BigInt_MutableBigInt_0(compiler::CodeAssemblerState* state_, TNode<BigInt> p_i) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BigInt> tmp0;
  TNode<BigInt> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = Convert_BigIntBase_MutableBigInt_0(state_, TNode<BigInt>{p_i});
    tmp1 = (TNode<BigInt>{tmp0});
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
  return TNode<BigInt>{tmp1};
}

TNode<Uint32T> kPositiveSign_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  TNode<Uint32T> tmp0;
    tmp0 = FromConstexpr_uint32_constexpr_int31_0(state_, 0);
  return TNode<Uint32T>{tmp0};
}

TNode<Uint32T> kNegativeSign_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  TNode<Uint32T> tmp0;
    tmp0 = FromConstexpr_uint32_constexpr_int31_0(state_, 1);
  return TNode<Uint32T>{tmp0};
}

TNode<BoolT> IsCanonicalized_0(compiler::CodeAssemblerState* state_, TNode<BigInt> p_bigint) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = BigIntBuiltinsAssembler(state_).ReadBigIntLength(TNode<BigInt>{p_bigint});
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp2 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{tmp1});
    ca_.Branch(tmp2, &block2, std::vector<Node*>{}, &block3, std::vector<Node*>{});
  }

  TNode<Uint32T> tmp3;
  TNode<Uint32T> tmp4;
  TNode<BoolT> tmp5;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp3 = BigIntBuiltinsAssembler(state_).ReadBigIntSign(TNode<BigInt>{p_bigint});
    tmp4 = kPositiveSign_0(state_);
    tmp5 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp3}, TNode<Uint32T>{tmp4});
    ca_.Goto(&block1, tmp5);
  }

  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<UintPtrT> tmp8;
  TNode<UintPtrT> tmp9;
  TNode<BoolT> tmp10;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp7 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{tmp6});
    tmp8 = CodeStubAssembler(state_).LoadBigIntDigit(TNode<BigInt>{p_bigint}, TNode<IntPtrT>{tmp7});
    tmp9 = FromConstexpr_uintptr_constexpr_int31_0(state_, 0);
    tmp10 = CodeStubAssembler(state_).WordNotEqual(TNode<UintPtrT>{tmp8}, TNode<UintPtrT>{tmp9});
    ca_.Goto(&block1, tmp10);
  }

  TNode<BoolT> phi_bb1_1;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_1);
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<BoolT>{phi_bb1_1};
}

TNode<Uint32T> InvertSign_0(compiler::CodeAssemblerState* state_, TNode<Uint32T> p_sign) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Uint32T> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = kPositiveSign_0(state_);
    tmp1 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{p_sign}, TNode<Uint32T>{tmp0});
    ca_.Branch(tmp1, &block2, std::vector<Node*>{}, &block3, std::vector<Node*>{});
  }

  TNode<Uint32T> tmp2;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp2 = kNegativeSign_0(state_);
    ca_.Goto(&block4, tmp2);
  }

  TNode<Uint32T> tmp3;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp3 = kPositiveSign_0(state_);
    ca_.Goto(&block4, tmp3);
  }

  TNode<Uint32T> phi_bb4_1;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_1);
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
  return TNode<Uint32T>{phi_bb4_1};
}

TNode<BigInt> AllocateEmptyBigIntNoThrow_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Uint32T> p_sign, TNode<IntPtrT> p_length, compiler::CodeAssemblerLabel* label_BigIntTooBig) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_intptr_0(state_, BigInt::kMaxLength);
    tmp1 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{p_length}, TNode<IntPtrT>{tmp0});
    ca_.Branch(tmp1, &block3, std::vector<Node*>{}, &block4, std::vector<Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(label_BigIntTooBig);
  }

  TNode<BigInt> tmp2;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp2 = CodeStubAssembler(state_).AllocateBigInt(TNode<IntPtrT>{p_length});
    BigIntBuiltinsAssembler(state_).WriteBigIntSignAndLength(TNode<BigInt>{tmp2}, TNode<Uint32T>{p_sign}, TNode<IntPtrT>{p_length});
    ca_.Goto(&block5);
  }

    ca_.Bind(&block5);
  return TNode<BigInt>{tmp2};
}

TNode<BigInt> AllocateEmptyBigInt_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Uint32T> p_sign, TNode<IntPtrT> p_length) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BigInt> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = AllocateEmptyBigIntNoThrow_0(state_, TNode<Context>{p_context}, TNode<Uint32T>{p_sign}, TNode<IntPtrT>{p_length}, &label1);
    ca_.Goto(&block4);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block5);
    }
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    CodeStubAssembler(state_).ThrowRangeError(TNode<Context>{p_context}, MessageTemplate::kBigIntTooBig);
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
  return TNode<BigInt>{tmp0};
}

TNode<Int32T> MutableBigIntAbsoluteCompare_0(compiler::CodeAssemblerState* state_, TNode<BigInt> p_x, TNode<BigInt> p_y) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Int32T> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = BigIntBuiltinsAssembler(state_).CppAbsoluteCompare(TNode<BigInt>{p_x}, TNode<BigInt>{p_y});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Int32T>{tmp0};
}

TNode<BigInt> MutableBigIntAbsoluteSub_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<BigInt> p_x, TNode<BigInt> p_y, TNode<Uint32T> p_resultSign) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BigInt> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BigInt> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BigInt> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<Uint32T> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<BoolT> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = BigIntBuiltinsAssembler(state_).ReadBigIntLength(TNode<BigInt>{p_x});
    tmp1 = BigIntBuiltinsAssembler(state_).ReadBigIntLength(TNode<BigInt>{p_y});
    tmp2 = BigIntBuiltinsAssembler(state_).ReadBigIntSign(TNode<BigInt>{p_x});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp4 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{tmp3});
    ca_.Branch(tmp4, &block6, std::vector<Node*>{}, &block7, std::vector<Node*>{});
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block1, p_x);
  }

  TNode<IntPtrT> tmp5;
  TNode<BoolT> tmp6;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp5 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp6 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{tmp5});
    ca_.Branch(tmp6, &block12, std::vector<Node*>{}, &block13, std::vector<Node*>{});
  }

  TNode<BoolT> tmp7;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp7 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{p_resultSign}, TNode<Uint32T>{tmp2});
    ca_.Branch(tmp7, &block14, std::vector<Node*>{}, &block15, std::vector<Node*>{});
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    ca_.Goto(&block16, p_x);
  }

  TNode<BigInt> tmp8;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp8 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kBigIntUnaryMinus, p_context, p_x));
    ca_.Goto(&block16, tmp8);
  }

  TNode<BigInt> phi_bb16_7;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_7);
    ca_.Goto(&block1, phi_bb16_7);
  }

  TNode<BigInt> tmp9;
  TNode<BigInt> tmp10;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp9 = AllocateEmptyBigInt_0(state_, TNode<Context>{p_context}, TNode<Uint32T>{p_resultSign}, TNode<IntPtrT>{tmp0});
    BigIntBuiltinsAssembler(state_).CppAbsoluteSubAndCanonicalize(TNode<BigInt>{tmp9}, TNode<BigInt>{p_x}, TNode<BigInt>{p_y});
    tmp10 = Convert_BigInt_MutableBigInt_0(state_, TNode<BigInt>{tmp9});
    ca_.Goto(&block1, tmp10);
  }

  TNode<BigInt> phi_bb1_4;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_4);
    ca_.Goto(&block18, phi_bb1_4);
  }

  TNode<BigInt> phi_bb18_4;
    ca_.Bind(&block18, &phi_bb18_4);
  return TNode<BigInt>{phi_bb18_4};
}

TNode<BigInt> MutableBigIntAbsoluteAdd_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<BigInt> p_xBigint, TNode<BigInt> p_yBigint, TNode<Uint32T> p_resultSign, compiler::CodeAssemblerLabel* label_BigIntTooBig) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, BigInt, BigInt> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BigInt> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BigInt> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BigInt> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = BigIntBuiltinsAssembler(state_).ReadBigIntLength(TNode<BigInt>{p_xBigint});
    tmp1 = BigIntBuiltinsAssembler(state_).ReadBigIntLength(TNode<BigInt>{p_yBigint});
    tmp2 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{tmp1});
    ca_.Branch(tmp2, &block3, std::vector<Node*>{}, &block4, std::vector<Node*>{tmp0, tmp1, p_xBigint, p_yBigint});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block4, tmp1, tmp0, p_yBigint, p_xBigint);
  }

  TNode<IntPtrT> phi_bb4_4;
  TNode<IntPtrT> phi_bb4_5;
  TNode<BigInt> phi_bb4_6;
  TNode<BigInt> phi_bb4_7;
  TNode<IntPtrT> tmp3;
  TNode<BoolT> tmp4;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_4, &phi_bb4_5, &phi_bb4_6, &phi_bb4_7);
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp4 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb4_4}, TNode<IntPtrT>{tmp3});
    ca_.Branch(tmp4, &block5, std::vector<Node*>{}, &block6, std::vector<Node*>{});
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    ca_.Goto(&block2, phi_bb4_6);
  }

  TNode<IntPtrT> tmp5;
  TNode<BoolT> tmp6;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp5 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp6 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb4_5}, TNode<IntPtrT>{tmp5});
    ca_.Branch(tmp6, &block11, std::vector<Node*>{}, &block12, std::vector<Node*>{});
  }

  TNode<Uint32T> tmp7;
  TNode<BoolT> tmp8;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp7 = BigIntBuiltinsAssembler(state_).ReadBigIntSign(TNode<BigInt>{phi_bb4_6});
    tmp8 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{p_resultSign}, TNode<Uint32T>{tmp7});
    ca_.Branch(tmp8, &block13, std::vector<Node*>{}, &block14, std::vector<Node*>{});
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    ca_.Goto(&block15, phi_bb4_6);
  }

  TNode<BigInt> tmp9;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp9 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kBigIntUnaryMinus, p_context, phi_bb4_6));
    ca_.Goto(&block15, tmp9);
  }

  TNode<BigInt> phi_bb15_8;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_8);
    ca_.Goto(&block2, phi_bb15_8);
  }

  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<BigInt> tmp12;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp11 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb4_4}, TNode<IntPtrT>{tmp10});
    compiler::CodeAssemblerLabel label13(&ca_);
    tmp12 = AllocateEmptyBigIntNoThrow_0(state_, TNode<Context>{p_context}, TNode<Uint32T>{p_resultSign}, TNode<IntPtrT>{tmp11}, &label13);
    ca_.Goto(&block17);
    if (label13.is_used()) {
      ca_.Bind(&label13);
      ca_.Goto(&block18);
    }
  }

  if (block18.is_used()) {
    ca_.Bind(&block18);
    ca_.Goto(label_BigIntTooBig);
  }

  TNode<BigInt> tmp14;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    BigIntBuiltinsAssembler(state_).CppAbsoluteAddAndCanonicalize(TNode<BigInt>{tmp12}, TNode<BigInt>{phi_bb4_6}, TNode<BigInt>{phi_bb4_7});
    tmp14 = Convert_BigInt_MutableBigInt_0(state_, TNode<BigInt>{tmp12});
    ca_.Goto(&block2, tmp14);
  }

  TNode<BigInt> phi_bb2_4;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_4);
    ca_.Goto(&block19, phi_bb2_4);
  }

  TNode<BigInt> phi_bb19_4;
    ca_.Bind(&block19, &phi_bb19_4);
  return TNode<BigInt>{phi_bb19_4};
}

TNode<BigInt> BigIntAddImpl_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<BigInt> p_x, TNode<BigInt> p_y, compiler::CodeAssemblerLabel* label_BigIntTooBig) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BigInt> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Uint32T> tmp0;
  TNode<Uint32T> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = BigIntBuiltinsAssembler(state_).ReadBigIntSign(TNode<BigInt>{p_x});
    tmp1 = BigIntBuiltinsAssembler(state_).ReadBigIntSign(TNode<BigInt>{p_y});
    tmp2 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp0}, TNode<Uint32T>{tmp1});
    ca_.Branch(tmp2, &block3, std::vector<Node*>{}, &block4, std::vector<Node*>{});
  }

  TNode<BigInt> tmp3;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label4(&ca_);
    tmp3 = MutableBigIntAbsoluteAdd_0(state_, TNode<Context>{p_context}, TNode<BigInt>{p_x}, TNode<BigInt>{p_y}, TNode<Uint32T>{tmp0}, &label4);
    ca_.Goto(&block5);
    if (label4.is_used()) {
      ca_.Bind(&label4);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(label_BigIntTooBig);
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    ca_.Goto(&block2, tmp3);
  }

  TNode<Int32T> tmp5;
  TNode<Int32T> tmp6;
  TNode<BoolT> tmp7;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp5 = MutableBigIntAbsoluteCompare_0(state_, TNode<BigInt>{p_x}, TNode<BigInt>{p_y});
    tmp6 = FromConstexpr_int32_constexpr_int31_0(state_, 0);
    tmp7 = CodeStubAssembler(state_).Int32GreaterThanOrEqual(TNode<Int32T>{tmp5}, TNode<Int32T>{tmp6});
    ca_.Branch(tmp7, &block7, std::vector<Node*>{}, &block8, std::vector<Node*>{});
  }

  TNode<BigInt> tmp8;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp8 = MutableBigIntAbsoluteSub_0(state_, TNode<Context>{p_context}, TNode<BigInt>{p_x}, TNode<BigInt>{p_y}, TNode<Uint32T>{tmp0});
    ca_.Goto(&block2, tmp8);
  }

  TNode<Uint32T> tmp9;
  TNode<BigInt> tmp10;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp9 = InvertSign_0(state_, TNode<Uint32T>{tmp0});
    tmp10 = MutableBigIntAbsoluteSub_0(state_, TNode<Context>{p_context}, TNode<BigInt>{p_y}, TNode<BigInt>{p_x}, TNode<Uint32T>{tmp9});
    ca_.Goto(&block2, tmp10);
  }

  TNode<BigInt> phi_bb2_3;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_3);
    ca_.Goto(&block9);
  }

    ca_.Bind(&block9);
  return TNode<BigInt>{phi_bb2_3};
}

TF_BUILTIN(BigIntAddNoThrow, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<BigInt> parameter1 = UncheckedCast<BigInt>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<BigInt> parameter2 = UncheckedCast<BigInt>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BigInt> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = BigIntAddImpl_0(state_, TNode<Context>{parameter0}, TNode<BigInt>{parameter1}, TNode<BigInt>{parameter2}, &label1);
    ca_.Goto(&block3);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block4);
    }
  }

  TNode<Smi> tmp2;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp2 = Convert_Smi_constexpr_int31_0(state_, 0);
    CodeStubAssembler(state_).Return(tmp2);
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TF_BUILTIN(BigIntAdd, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Numeric> parameter1 = UncheckedCast<Numeric>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Numeric> parameter2 = UncheckedCast<Numeric>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BigInt> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_BigInt_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1);
    ca_.Goto(&block5);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block4);
  }

  TNode<BigInt> tmp2;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_BigInt_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2}, &label3);
    ca_.Goto(&block7);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block8);
    }
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block4);
  }

  TNode<BigInt> tmp4;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    compiler::CodeAssemblerLabel label5(&ca_);
    tmp4 = BigIntAddImpl_0(state_, TNode<Context>{parameter0}, TNode<BigInt>{tmp0}, TNode<BigInt>{tmp2}, &label5);
    ca_.Goto(&block9);
    if (label5.is_used()) {
      ca_.Bind(&label5);
      ca_.Goto(&block10);
    }
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    CodeStubAssembler(state_).ThrowRangeError(TNode<Context>{parameter0}, MessageTemplate::kBigIntTooBig);
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    CodeStubAssembler(state_).Return(tmp4);
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, MessageTemplate::kBigIntMixedTypes);
  }
}

TNode<BigInt> BigIntSubtractImpl_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<BigInt> p_x, TNode<BigInt> p_y, compiler::CodeAssemblerLabel* label_BigIntTooBig) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BigInt> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Uint32T> tmp0;
  TNode<Uint32T> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = BigIntBuiltinsAssembler(state_).ReadBigIntSign(TNode<BigInt>{p_x});
    tmp1 = BigIntBuiltinsAssembler(state_).ReadBigIntSign(TNode<BigInt>{p_y});
    tmp2 = CodeStubAssembler(state_).Word32NotEqual(TNode<Uint32T>{tmp0}, TNode<Uint32T>{tmp1});
    ca_.Branch(tmp2, &block3, std::vector<Node*>{}, &block4, std::vector<Node*>{});
  }

  TNode<BigInt> tmp3;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label4(&ca_);
    tmp3 = MutableBigIntAbsoluteAdd_0(state_, TNode<Context>{p_context}, TNode<BigInt>{p_x}, TNode<BigInt>{p_y}, TNode<Uint32T>{tmp0}, &label4);
    ca_.Goto(&block5);
    if (label4.is_used()) {
      ca_.Bind(&label4);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(label_BigIntTooBig);
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    ca_.Goto(&block2, tmp3);
  }

  TNode<Int32T> tmp5;
  TNode<Int32T> tmp6;
  TNode<BoolT> tmp7;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp5 = MutableBigIntAbsoluteCompare_0(state_, TNode<BigInt>{p_x}, TNode<BigInt>{p_y});
    tmp6 = FromConstexpr_int32_constexpr_int31_0(state_, 0);
    tmp7 = CodeStubAssembler(state_).Int32GreaterThanOrEqual(TNode<Int32T>{tmp5}, TNode<Int32T>{tmp6});
    ca_.Branch(tmp7, &block7, std::vector<Node*>{}, &block8, std::vector<Node*>{});
  }

  TNode<BigInt> tmp8;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp8 = MutableBigIntAbsoluteSub_0(state_, TNode<Context>{p_context}, TNode<BigInt>{p_x}, TNode<BigInt>{p_y}, TNode<Uint32T>{tmp0});
    ca_.Goto(&block2, tmp8);
  }

  TNode<Uint32T> tmp9;
  TNode<BigInt> tmp10;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp9 = InvertSign_0(state_, TNode<Uint32T>{tmp0});
    tmp10 = MutableBigIntAbsoluteSub_0(state_, TNode<Context>{p_context}, TNode<BigInt>{p_y}, TNode<BigInt>{p_x}, TNode<Uint32T>{tmp9});
    ca_.Goto(&block2, tmp10);
  }

  TNode<BigInt> phi_bb2_3;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_3);
    ca_.Goto(&block9);
  }

    ca_.Bind(&block9);
  return TNode<BigInt>{phi_bb2_3};
}

TF_BUILTIN(BigIntSubtractNoThrow, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<BigInt> parameter1 = UncheckedCast<BigInt>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<BigInt> parameter2 = UncheckedCast<BigInt>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BigInt> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = BigIntSubtractImpl_0(state_, TNode<Context>{parameter0}, TNode<BigInt>{parameter1}, TNode<BigInt>{parameter2}, &label1);
    ca_.Goto(&block3);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block4);
    }
  }

  TNode<Smi> tmp2;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp2 = Convert_Smi_constexpr_int31_0(state_, 0);
    CodeStubAssembler(state_).Return(tmp2);
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TF_BUILTIN(BigIntSubtract, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Numeric> parameter1 = UncheckedCast<Numeric>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Numeric> parameter2 = UncheckedCast<Numeric>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BigInt> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_BigInt_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1);
    ca_.Goto(&block5);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block4);
  }

  TNode<BigInt> tmp2;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_BigInt_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2}, &label3);
    ca_.Goto(&block7);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block8);
    }
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block4);
  }

  TNode<BigInt> tmp4;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    compiler::CodeAssemblerLabel label5(&ca_);
    tmp4 = BigIntSubtractImpl_0(state_, TNode<Context>{parameter0}, TNode<BigInt>{tmp0}, TNode<BigInt>{tmp2}, &label5);
    ca_.Goto(&block9);
    if (label5.is_used()) {
      ca_.Bind(&label5);
      ca_.Goto(&block10);
    }
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    CodeStubAssembler(state_).ThrowRangeError(TNode<Context>{parameter0}, MessageTemplate::kBigIntTooBig);
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    CodeStubAssembler(state_).Return(tmp4);
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, MessageTemplate::kBigIntMixedTypes);
  }
}

TF_BUILTIN(BigIntUnaryMinus, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<BigInt> parameter1 = UncheckedCast<BigInt>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = BigIntBuiltinsAssembler(state_).ReadBigIntLength(TNode<BigInt>{parameter1});
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp2 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{tmp1});
    ca_.Branch(tmp2, &block1, std::vector<Node*>{}, &block2, std::vector<Node*>{});
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    CodeStubAssembler(state_).Return(parameter1);
  }

  TNode<Uint32T> tmp3;
  TNode<Uint32T> tmp4;
  TNode<BigInt> tmp5;
  TNode<IntPtrT> tmp6;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp3 = BigIntBuiltinsAssembler(state_).ReadBigIntSign(TNode<BigInt>{parameter1});
    tmp4 = InvertSign_0(state_, TNode<Uint32T>{tmp3});
    tmp5 = AllocateEmptyBigInt_0(state_, TNode<Context>{parameter0}, TNode<Uint32T>{tmp4}, TNode<IntPtrT>{tmp0});
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    ca_.Goto(&block5, tmp6);
  }

  TNode<IntPtrT> phi_bb5_4;
  TNode<BoolT> tmp7;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_4);
    tmp7 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb5_4}, TNode<IntPtrT>{tmp0});
    ca_.Branch(tmp7, &block3, std::vector<Node*>{phi_bb5_4}, &block4, std::vector<Node*>{phi_bb5_4});
  }

  TNode<IntPtrT> phi_bb3_4;
  TNode<UintPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_4);
    tmp8 = CodeStubAssembler(state_).LoadBigIntDigit(TNode<BigInt>{parameter1}, TNode<IntPtrT>{phi_bb3_4});
    CodeStubAssembler(state_).StoreBigIntDigit(TNode<BigInt>{tmp5}, TNode<IntPtrT>{phi_bb3_4}, TNode<UintPtrT>{tmp8});
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp10 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb3_4}, TNode<IntPtrT>{tmp9});
    ca_.Goto(&block5, tmp10);
  }

  TNode<IntPtrT> phi_bb4_4;
  TNode<BigInt> tmp11;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_4);
    tmp11 = Convert_BigInt_MutableBigInt_0(state_, TNode<BigInt>{tmp5});
    CodeStubAssembler(state_).Return(tmp11);
  }
}

TNode<BigInt> DownCastForTorqueClass_BigIntBase_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Map> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp1 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{p_o, tmp0});
    if (((CodeStubAssembler(state_).ConstexprInt31Equal(static_cast<InstanceType>(65), static_cast<InstanceType>(65))))) {
      ca_.Goto(&block3);
    } else {
      ca_.Goto(&block4);
    }
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    if ((false)) {
      ca_.Goto(&block6);
    } else {
      ca_.Goto(&block7);
    }
  }

  TNode<Map> tmp2;
  TNode<BoolT> tmp3;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp2 = CodeStubAssembler(state_).GetClassMapConstant<void>();
    tmp3 = CodeStubAssembler(state_).TaggedNotEqual(TNode<HeapObject>{tmp1}, TNode<HeapObject>{tmp2});
    ca_.Branch(tmp3, &block9, std::vector<Node*>{}, &block10, std::vector<Node*>{});
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    ca_.Goto(&block1);
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    ca_.Goto(&block8);
  }

  TNode<IntPtrT> tmp4;
  TNode<Uint16T> tmp5;
  TNode<Uint32T> tmp6;
  TNode<BoolT> tmp7;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp5 = CodeStubAssembler(state_).LoadReference<Uint16T>(CodeStubAssembler::Reference{tmp1, tmp4});
    tmp6 = FromConstexpr_uint32_constexpr_uint32_0(state_, static_cast<InstanceType>(65));
    tmp7 = CodeStubAssembler(state_).Word32NotEqual(TNode<Uint32T>{tmp5}, TNode<Uint32T>{tmp6});
    ca_.Branch(tmp7, &block11, std::vector<Node*>{}, &block12, std::vector<Node*>{});
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    ca_.Goto(&block1);
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    ca_.Goto(&block8);
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block5);
  }

  TNode<Int32T> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<Uint16T> tmp10;
  TNode<Uint16T> tmp11;
  TNode<Int32T> tmp12;
  TNode<Uint16T> tmp13;
  TNode<Uint16T> tmp14;
  TNode<Int32T> tmp15;
  TNode<Int32T> tmp16;
  TNode<Uint32T> tmp17;
  TNode<Uint32T> tmp18;
  TNode<BoolT> tmp19;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp8 = FromConstexpr_int32_constexpr_int32_0(state_, (CodeStubAssembler(state_).ConstexprUint32Sub(static_cast<InstanceType>(65), static_cast<InstanceType>(65))));
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp10 = CodeStubAssembler(state_).LoadReference<Uint16T>(CodeStubAssembler::Reference{tmp1, tmp9});
    tmp11 = Convert_uint16_InstanceType_0(state_, TNode<Uint16T>{tmp10});
    tmp12 = Convert_int32_uint16_0(state_, TNode<Uint16T>{tmp11});
    tmp13 = FromConstexpr_InstanceType_constexpr_InstanceType_0(state_, static_cast<InstanceType>(65));
    tmp14 = Convert_uint16_InstanceType_0(state_, TNode<Uint16T>{tmp13});
    tmp15 = Convert_int32_uint16_0(state_, TNode<Uint16T>{tmp14});
    tmp16 = CodeStubAssembler(state_).Int32Sub(TNode<Int32T>{tmp12}, TNode<Int32T>{tmp15});
    tmp17 = CodeStubAssembler(state_).Unsigned(TNode<Int32T>{tmp16});
    tmp18 = CodeStubAssembler(state_).Unsigned(TNode<Int32T>{tmp8});
    tmp19 = CodeStubAssembler(state_).Uint32GreaterThan(TNode<Uint32T>{tmp17}, TNode<Uint32T>{tmp18});
    ca_.Branch(tmp19, &block13, std::vector<Node*>{}, &block14, std::vector<Node*>{});
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    ca_.Goto(&block1);
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    ca_.Goto(&block5);
  }

  TNode<BigInt> tmp20;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp20 = TORQUE_CAST(TNode<HeapObject>{p_o});
    ca_.Goto(&block15);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_CastError);
  }

    ca_.Bind(&block15);
  return TNode<BigInt>{tmp20};
}

TNode<BigInt> Convert_BigIntBase_MutableBigInt_0(compiler::CodeAssemblerState* state_, TNode<BigInt> p_i) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<BigInt>{p_i};
}

TNode<BigInt> Cast_BigInt_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<HeapObject> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = CodeStubAssembler(state_).TaggedToHeapObject(TNode<Object>{p_o}, &label1);
    ca_.Goto(&block3);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block4);
    }
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    ca_.Goto(&block1);
  }

  TNode<BigInt> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_BigInt_0(state_, TNode<HeapObject>{tmp0}, &label3);
    ca_.Goto(&block5);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block1);
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    ca_.Goto(&block7);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_CastError);
  }

    ca_.Bind(&block7);
  return TNode<BigInt>{tmp2};
}

}  // namespace internal
}  // namespace v8

