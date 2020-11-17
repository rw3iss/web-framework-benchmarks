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

TNode<IntPtrT> FromConstexpr_PromiseValueThunkOrReasonContextSlot_constexpr_kValueSlot_0(compiler::CodeAssemblerState* state_, PromiseBuiltins::PromiseValueThunkOrReasonContextSlot p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ca_.IntPtrConstant(CastToUnderlyingTypeIfEnum(p_o));
    tmp1 = (TNode<IntPtrT>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<IntPtrT>{tmp1};
}

TNode<IntPtrT> FromConstexpr_PromiseValueThunkOrReasonContextSlot_constexpr_kPromiseValueThunkOrReasonContextLength_0(compiler::CodeAssemblerState* state_, PromiseBuiltins::PromiseValueThunkOrReasonContextSlot p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ca_.IntPtrConstant(CastToUnderlyingTypeIfEnum(p_o));
    tmp1 = (TNode<IntPtrT>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<IntPtrT>{tmp1};
}

TNode<IntPtrT> kValueSlot_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  TNode<IntPtrT> tmp0;
    tmp0 = FromConstexpr_PromiseValueThunkOrReasonContextSlot_constexpr_kValueSlot_0(state_, PromiseBuiltins::PromiseValueThunkOrReasonContextSlot::kValueSlot);
  TNode<IntPtrT> tmp1;
    tmp1 = (TNode<IntPtrT>{tmp0});
  return TNode<IntPtrT>{tmp1};
}

TNode<IntPtrT> FromConstexpr_PromiseFinallyContextSlot_constexpr_kOnFinallySlot_0(compiler::CodeAssemblerState* state_, PromiseBuiltins::PromiseFinallyContextSlot p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ca_.IntPtrConstant(CastToUnderlyingTypeIfEnum(p_o));
    tmp1 = (TNode<IntPtrT>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<IntPtrT>{tmp1};
}

TNode<IntPtrT> FromConstexpr_PromiseFinallyContextSlot_constexpr_kConstructorSlot_0(compiler::CodeAssemblerState* state_, PromiseBuiltins::PromiseFinallyContextSlot p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ca_.IntPtrConstant(CastToUnderlyingTypeIfEnum(p_o));
    tmp1 = (TNode<IntPtrT>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<IntPtrT>{tmp1};
}

TNode<IntPtrT> FromConstexpr_PromiseFinallyContextSlot_constexpr_kPromiseFinallyContextLength_0(compiler::CodeAssemblerState* state_, PromiseBuiltins::PromiseFinallyContextSlot p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ca_.IntPtrConstant(CastToUnderlyingTypeIfEnum(p_o));
    tmp1 = (TNode<IntPtrT>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<IntPtrT>{tmp1};
}

TNode<IntPtrT> kOnFinallySlot_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  TNode<IntPtrT> tmp0;
    tmp0 = FromConstexpr_PromiseFinallyContextSlot_constexpr_kOnFinallySlot_0(state_, PromiseBuiltins::PromiseFinallyContextSlot::kOnFinallySlot);
  TNode<IntPtrT> tmp1;
    tmp1 = (TNode<IntPtrT>{tmp0});
  return TNode<IntPtrT>{tmp1};
}

TNode<IntPtrT> kConstructorSlot_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  TNode<IntPtrT> tmp0;
    tmp0 = FromConstexpr_PromiseFinallyContextSlot_constexpr_kConstructorSlot_0(state_, PromiseBuiltins::PromiseFinallyContextSlot::kConstructorSlot);
  TNode<IntPtrT> tmp1;
    tmp1 = (TNode<IntPtrT>{tmp0});
  return TNode<IntPtrT>{tmp1};
}

TF_BUILTIN(PromiseValueThunkFinally, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kReceiver));
USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Context> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<HeapObject> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<Object> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = (TNode<Context>{parameter0});
    tmp1 = kValueSlot_0(state_);
    std::tie(tmp2, tmp3) = ContextSlot_PromiseValueThunkOrReasonContext_PromiseValueThunkOrReasonContext_JSAny_0(state_, TNode<Context>{tmp0}, TNode<IntPtrT>{tmp1}).Flatten();
    tmp4 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp2, tmp3});
    CodeStubAssembler(state_).Return(tmp4);
  }
}

TF_BUILTIN(PromiseThrowerFinally, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kReceiver));
USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Context> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<HeapObject> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<Object> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = (TNode<Context>{parameter0});
    tmp1 = kValueSlot_0(state_);
    std::tie(tmp2, tmp3) = ContextSlot_PromiseValueThunkOrReasonContext_PromiseValueThunkOrReasonContext_JSAny_0(state_, TNode<Context>{tmp0}, TNode<IntPtrT>{tmp1}).Flatten();
    tmp4 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp2, tmp3});
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrow, tmp0, tmp4);
    CodeStubAssembler(state_).Unreachable();
  }
}

TNode<JSFunction> CreateThrowerFunction_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<NativeContext> p_nativeContext, TNode<Object> p_reason) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Context> tmp1;
  TNode<Context> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<HeapObject> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<Map> tmp7;
  TNode<SharedFunctionInfo> tmp8;
  TNode<JSFunction> tmp9;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_intptr_0(state_, PromiseBuiltins::PromiseValueThunkOrReasonContextSlot::kPromiseValueThunkOrReasonContextLength);
    tmp1 = AllocateSyntheticFunctionContext_1(state_, TNode<NativeContext>{p_nativeContext}, TNode<IntPtrT>{tmp0});
    tmp2 = (TNode<Context>{tmp1});
    tmp3 = kValueSlot_0(state_);
    InitContextSlot_PromiseValueThunkOrReasonContext_PromiseValueThunkOrReasonContext_JSAny_JSAny_0(state_, TNode<Context>{tmp2}, TNode<IntPtrT>{tmp3}, TNode<Object>{p_reason});
    tmp4 = STRICT_FUNCTION_WITHOUT_PROTOTYPE_MAP_INDEX_0(state_);
    std::tie(tmp5, tmp6) = ContextSlot_NativeContext_NativeContext_Map_0(state_, TNode<NativeContext>{p_nativeContext}, TNode<IntPtrT>{tmp4}).Flatten();
    tmp7 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp5, tmp6});
    tmp8 = CodeStubAssembler(state_).PromiseThrowerFinallySharedFunConstant();
    tmp9 = CodeStubAssembler(state_).AllocateFunctionWithMapAndContext(TNode<Map>{tmp7}, TNode<SharedFunctionInfo>{tmp8}, TNode<Context>{tmp2});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<JSFunction>{tmp9};
}

TF_BUILTIN(PromiseCatchFinally, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kReceiver));
USE(parameter1);
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::kReason));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Context> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<HeapObject> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<JSReceiver> tmp4;
  TNode<Oddball> tmp5;
  TNode<Object> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<HeapObject> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<JSReceiver> tmp10;
  TNode<Object> tmp11;
  TNode<NativeContext> tmp12;
  TNode<JSFunction> tmp13;
  TNode<Object> tmp14;
  TNode<Object> tmp15;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = (TNode<Context>{parameter0});
    tmp1 = kOnFinallySlot_0(state_);
    std::tie(tmp2, tmp3) = ContextSlot_PromiseFinallyContext_PromiseFinallyContext_Callable_0(state_, TNode<Context>{tmp0}, TNode<IntPtrT>{tmp1}).Flatten();
    tmp4 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{tmp2, tmp3});
    tmp5 = Undefined_0(state_);
    tmp6 = CodeStubAssembler(state_).Call(TNode<Context>{tmp0}, TNode<Object>{tmp4}, TNode<Object>{tmp5});
    tmp7 = kConstructorSlot_0(state_);
    std::tie(tmp8, tmp9) = ContextSlot_PromiseFinallyContext_PromiseFinallyContext_Constructor_0(state_, TNode<Context>{tmp0}, TNode<IntPtrT>{tmp7}).Flatten();
    tmp10 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{tmp8, tmp9});
    tmp11 = CodeStubAssembler(state_).CallBuiltin(Builtins::kPromiseResolve, tmp0, tmp10, tmp6);
    tmp12 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{tmp0});
    tmp13 = CreateThrowerFunction_0(state_, TNode<Context>{tmp0}, TNode<NativeContext>{tmp12}, TNode<Object>{parameter2});
    tmp14 = InvokeThen_0(state_, TNode<Context>{tmp0}, TNode<NativeContext>{tmp12}, TNode<Object>{tmp11}, TNode<Object>{tmp13});
    tmp15 = UnsafeCast_JSAny_0(state_, TNode<Context>{tmp0}, TNode<Object>{tmp14});
    CodeStubAssembler(state_).Return(tmp15);
  }
}

TNode<JSFunction> CreateValueThunkFunction_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<NativeContext> p_nativeContext, TNode<Object> p_value) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Context> tmp1;
  TNode<Context> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<HeapObject> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<Map> tmp7;
  TNode<SharedFunctionInfo> tmp8;
  TNode<JSFunction> tmp9;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_intptr_0(state_, PromiseBuiltins::PromiseValueThunkOrReasonContextSlot::kPromiseValueThunkOrReasonContextLength);
    tmp1 = AllocateSyntheticFunctionContext_1(state_, TNode<NativeContext>{p_nativeContext}, TNode<IntPtrT>{tmp0});
    tmp2 = (TNode<Context>{tmp1});
    tmp3 = kValueSlot_0(state_);
    InitContextSlot_PromiseValueThunkOrReasonContext_PromiseValueThunkOrReasonContext_JSAny_JSAny_0(state_, TNode<Context>{tmp2}, TNode<IntPtrT>{tmp3}, TNode<Object>{p_value});
    tmp4 = STRICT_FUNCTION_WITHOUT_PROTOTYPE_MAP_INDEX_0(state_);
    std::tie(tmp5, tmp6) = ContextSlot_NativeContext_NativeContext_Map_0(state_, TNode<NativeContext>{p_nativeContext}, TNode<IntPtrT>{tmp4}).Flatten();
    tmp7 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp5, tmp6});
    tmp8 = CodeStubAssembler(state_).PromiseValueThunkFinallySharedFunConstant();
    tmp9 = CodeStubAssembler(state_).AllocateFunctionWithMapAndContext(TNode<Map>{tmp7}, TNode<SharedFunctionInfo>{tmp8}, TNode<Context>{tmp2});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<JSFunction>{tmp9};
}

TF_BUILTIN(PromiseThenFinally, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kReceiver));
USE(parameter1);
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::kValue));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Context> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<HeapObject> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<JSReceiver> tmp4;
  TNode<Oddball> tmp5;
  TNode<Object> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<HeapObject> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<JSReceiver> tmp10;
  TNode<Object> tmp11;
  TNode<NativeContext> tmp12;
  TNode<JSFunction> tmp13;
  TNode<Object> tmp14;
  TNode<Object> tmp15;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = (TNode<Context>{parameter0});
    tmp1 = kOnFinallySlot_0(state_);
    std::tie(tmp2, tmp3) = ContextSlot_PromiseFinallyContext_PromiseFinallyContext_Callable_0(state_, TNode<Context>{tmp0}, TNode<IntPtrT>{tmp1}).Flatten();
    tmp4 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{tmp2, tmp3});
    tmp5 = Undefined_0(state_);
    tmp6 = CodeStubAssembler(state_).Call(TNode<Context>{tmp0}, TNode<Object>{tmp4}, TNode<Object>{tmp5});
    tmp7 = kConstructorSlot_0(state_);
    std::tie(tmp8, tmp9) = ContextSlot_PromiseFinallyContext_PromiseFinallyContext_Constructor_0(state_, TNode<Context>{tmp0}, TNode<IntPtrT>{tmp7}).Flatten();
    tmp10 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{tmp8, tmp9});
    tmp11 = CodeStubAssembler(state_).CallBuiltin(Builtins::kPromiseResolve, tmp0, tmp10, tmp6);
    tmp12 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{tmp0});
    tmp13 = CreateValueThunkFunction_0(state_, TNode<Context>{tmp0}, TNode<NativeContext>{tmp12}, TNode<Object>{parameter2});
    tmp14 = InvokeThen_0(state_, TNode<Context>{tmp0}, TNode<NativeContext>{tmp12}, TNode<Object>{tmp11}, TNode<Object>{tmp13});
    tmp15 = UnsafeCast_JSAny_0(state_, TNode<Context>{tmp0}, TNode<Object>{tmp14});
    CodeStubAssembler(state_).Return(tmp15);
  }
}

TorqueStructPromiseFinallyFunctions_0 CreatePromiseFinallyFunctions_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<NativeContext> p_nativeContext, TNode<JSReceiver> p_onFinally, TNode<JSReceiver> p_constructor) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Context> tmp1;
  TNode<Context> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<HeapObject> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<Map> tmp8;
  TNode<SharedFunctionInfo> tmp9;
  TNode<JSFunction> tmp10;
  TNode<SharedFunctionInfo> tmp11;
  TNode<JSFunction> tmp12;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_intptr_0(state_, PromiseBuiltins::PromiseFinallyContextSlot::kPromiseFinallyContextLength);
    tmp1 = AllocateSyntheticFunctionContext_1(state_, TNode<NativeContext>{p_nativeContext}, TNode<IntPtrT>{tmp0});
    tmp2 = (TNode<Context>{tmp1});
    tmp3 = kOnFinallySlot_0(state_);
    InitContextSlot_PromiseFinallyContext_PromiseFinallyContext_Callable_Callable_0(state_, TNode<Context>{tmp2}, TNode<IntPtrT>{tmp3}, TNode<JSReceiver>{p_onFinally});
    tmp4 = kConstructorSlot_0(state_);
    InitContextSlot_PromiseFinallyContext_PromiseFinallyContext_Constructor_Constructor_0(state_, TNode<Context>{tmp2}, TNode<IntPtrT>{tmp4}, TNode<JSReceiver>{p_constructor});
    tmp5 = STRICT_FUNCTION_WITHOUT_PROTOTYPE_MAP_INDEX_0(state_);
    std::tie(tmp6, tmp7) = ContextSlot_NativeContext_NativeContext_Map_0(state_, TNode<NativeContext>{p_nativeContext}, TNode<IntPtrT>{tmp5}).Flatten();
    tmp8 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp6, tmp7});
    tmp9 = CodeStubAssembler(state_).PromiseThenFinallySharedFunConstant();
    tmp10 = CodeStubAssembler(state_).AllocateFunctionWithMapAndContext(TNode<Map>{tmp8}, TNode<SharedFunctionInfo>{tmp9}, TNode<Context>{tmp2});
    tmp11 = CodeStubAssembler(state_).PromiseCatchFinallySharedFunConstant();
    tmp12 = CodeStubAssembler(state_).AllocateFunctionWithMapAndContext(TNode<Map>{tmp8}, TNode<SharedFunctionInfo>{tmp11}, TNode<Context>{tmp2});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructPromiseFinallyFunctions_0{TNode<JSFunction>{tmp10}, TNode<JSFunction>{tmp12}};
}

TF_BUILTIN(PromisePrototypeFinally, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kReceiver));
USE(parameter1);
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::kOnFinally));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSReceiver> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object, Object> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1);
    ca_.Goto(&block3);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block4);
    }
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, MessageTemplate::kCalledOnNonObject, "Promise.prototype.finally");
  }

  TNode<NativeContext> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<HeapObject> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<JSFunction> tmp6;
  TNode<JSReceiver> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Map> tmp9;
  TNode<BoolT> tmp10;
  TNode<BoolT> tmp11;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{parameter0});
    tmp3 = PROMISE_FUNCTION_INDEX_0(state_);
    std::tie(tmp4, tmp5) = NativeContextSlot_Context_JSFunction_0(state_, TNode<Context>{parameter0}, TNode<IntPtrT>{tmp3}).Flatten();
    tmp6 = CodeStubAssembler(state_).LoadReference<JSFunction>(CodeStubAssembler::Reference{tmp4, tmp5});
    tmp7 = UnsafeCast_Constructor_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp6});
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp9 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp0, tmp8});
    tmp10 = CodeStubAssembler(state_).IsJSPromiseMap(TNode<Map>{tmp9});
    tmp11 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp10});
    ca_.Branch(tmp11, &block7, std::vector<Node*>{}, &block8, std::vector<Node*>{});
  }

  TNode<BoolT> tmp12;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp12 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block9, tmp12);
  }

  TNode<BoolT> tmp13;
  TNode<BoolT> tmp14;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp13 = IsPromiseSpeciesLookupChainIntact_0(state_, TNode<NativeContext>{tmp2}, TNode<Map>{tmp9});
    tmp14 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp13});
    ca_.Goto(&block9, tmp14);
  }

  TNode<BoolT> phi_bb9_9;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_9);
    ca_.Branch(phi_bb9_9, &block5, std::vector<Node*>{}, &block6, std::vector<Node*>{tmp7});
  }

  TNode<JSReceiver> tmp15;
  TNode<JSReceiver> tmp16;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp15 = CodeStubAssembler(state_).SpeciesConstructor(TNode<Context>{parameter0}, TNode<Object>{tmp0}, TNode<JSReceiver>{tmp6});
    tmp16 = UnsafeCast_Constructor_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp15});
    ca_.Goto(&block6, tmp16);
  }

  TNode<JSReceiver> phi_bb6_6;
  TNode<JSReceiver> tmp17;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_6);
    compiler::CodeAssemblerLabel label18(&ca_);
    tmp17 = Cast_Callable_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2}, &label18);
    ca_.Goto(&block16);
    if (label18.is_used()) {
      ca_.Bind(&label18);
      ca_.Goto(&block17);
    }
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    ca_.Goto(&block14, parameter2, parameter2);
  }

  TNode<JSFunction> tmp19;
  TNode<JSFunction> tmp20;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    std::tie(tmp19, tmp20) = CreatePromiseFinallyFunctions_0(state_, TNode<Context>{parameter0}, TNode<NativeContext>{tmp2}, TNode<JSReceiver>{tmp17}, TNode<JSReceiver>{phi_bb6_6}).Flatten();
    ca_.Goto(&block14, tmp19, tmp20);
  }

  TNode<Object> phi_bb14_8;
  TNode<Object> phi_bb14_9;
  TNode<Object> tmp21;
  TNode<Object> tmp22;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_8, &phi_bb14_9);
    tmp21 = InvokeThen_1(state_, TNode<Context>{parameter0}, TNode<NativeContext>{tmp2}, TNode<Object>{parameter1}, TNode<Object>{phi_bb14_8}, TNode<Object>{phi_bb14_9});
    tmp22 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp21});
    CodeStubAssembler(state_).Return(tmp22);
  }
}

TorqueStructReference_JSAny_0 ContextSlot_PromiseValueThunkOrReasonContext_PromiseValueThunkOrReasonContext_JSAny_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<IntPtrT> p_index) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Smi> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<UintPtrT> tmp5;
  TNode<UintPtrT> tmp6;
  TNode<BoolT> tmp7;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp3 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_context, tmp2});
    tmp4 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp3});
    tmp5 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{p_index});
    tmp6 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp4});
    tmp7 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp5}, TNode<UintPtrT>{tmp6});
    ca_.Branch(tmp7, &block6, std::vector<Node*>{}, &block7, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<HeapObject> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<HeapObject> tmp13;
  TNode<IntPtrT> tmp14;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp9 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{p_index}, TNode<IntPtrT>{tmp8});
    tmp10 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{tmp9});
    std::tie(tmp11, tmp12) = NewReference_Object_0(state_, TNode<HeapObject>{p_context}, TNode<IntPtrT>{tmp10}).Flatten();
    std::tie(tmp13, tmp14) = ReferenceCast_JSAny_Object_0(state_, TorqueStructReference_Object_0{TNode<HeapObject>{tmp11}, TNode<IntPtrT>{tmp12}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Goto(&block9);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block9);
  return TorqueStructReference_JSAny_0{TNode<HeapObject>{tmp13}, TNode<IntPtrT>{tmp14}, TorqueStructUnsafe_0{}};
}

void InitContextSlot_PromiseValueThunkOrReasonContext_PromiseValueThunkOrReasonContext_JSAny_JSAny_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<IntPtrT> p_index, TNode<Object> p_value) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Smi> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<UintPtrT> tmp5;
  TNode<UintPtrT> tmp6;
  TNode<BoolT> tmp7;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp3 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_context, tmp2});
    tmp4 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp3});
    tmp5 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{p_index});
    tmp6 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp4});
    tmp7 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp5}, TNode<UintPtrT>{tmp6});
    ca_.Branch(tmp7, &block17, std::vector<Node*>{}, &block18, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<HeapObject> tmp11;
  TNode<IntPtrT> tmp12;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp9 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{p_index}, TNode<IntPtrT>{tmp8});
    tmp10 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{tmp9});
    std::tie(tmp11, tmp12) = NewReference_Object_0(state_, TNode<HeapObject>{p_context}, TNode<IntPtrT>{tmp10}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp11, tmp12}, p_value);
    ca_.Goto(&block20);
  }

  if (block18.is_used()) {
    ca_.Bind(&block18);
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block20);
}

TorqueStructReference_Callable_0 ContextSlot_PromiseFinallyContext_PromiseFinallyContext_Callable_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<IntPtrT> p_index) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Smi> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<UintPtrT> tmp5;
  TNode<UintPtrT> tmp6;
  TNode<BoolT> tmp7;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp3 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_context, tmp2});
    tmp4 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp3});
    tmp5 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{p_index});
    tmp6 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp4});
    tmp7 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp5}, TNode<UintPtrT>{tmp6});
    ca_.Branch(tmp7, &block6, std::vector<Node*>{}, &block7, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<HeapObject> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<HeapObject> tmp13;
  TNode<IntPtrT> tmp14;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp9 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{p_index}, TNode<IntPtrT>{tmp8});
    tmp10 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{tmp9});
    std::tie(tmp11, tmp12) = NewReference_Object_0(state_, TNode<HeapObject>{p_context}, TNode<IntPtrT>{tmp10}).Flatten();
    std::tie(tmp13, tmp14) = ReferenceCast_Callable_Object_0(state_, TorqueStructReference_Object_0{TNode<HeapObject>{tmp11}, TNode<IntPtrT>{tmp12}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Goto(&block9);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block9);
  return TorqueStructReference_Callable_0{TNode<HeapObject>{tmp13}, TNode<IntPtrT>{tmp14}, TorqueStructUnsafe_0{}};
}

TorqueStructReference_Constructor_0 ContextSlot_PromiseFinallyContext_PromiseFinallyContext_Constructor_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<IntPtrT> p_index) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Smi> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<UintPtrT> tmp5;
  TNode<UintPtrT> tmp6;
  TNode<BoolT> tmp7;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp3 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_context, tmp2});
    tmp4 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp3});
    tmp5 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{p_index});
    tmp6 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp4});
    tmp7 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp5}, TNode<UintPtrT>{tmp6});
    ca_.Branch(tmp7, &block6, std::vector<Node*>{}, &block7, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<HeapObject> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<HeapObject> tmp13;
  TNode<IntPtrT> tmp14;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp9 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{p_index}, TNode<IntPtrT>{tmp8});
    tmp10 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{tmp9});
    std::tie(tmp11, tmp12) = NewReference_Object_0(state_, TNode<HeapObject>{p_context}, TNode<IntPtrT>{tmp10}).Flatten();
    std::tie(tmp13, tmp14) = ReferenceCast_Constructor_Object_0(state_, TorqueStructReference_Object_0{TNode<HeapObject>{tmp11}, TNode<IntPtrT>{tmp12}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Goto(&block9);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block9);
  return TorqueStructReference_Constructor_0{TNode<HeapObject>{tmp13}, TNode<IntPtrT>{tmp14}, TorqueStructUnsafe_0{}};
}

void InitContextSlot_PromiseFinallyContext_PromiseFinallyContext_Callable_Callable_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<IntPtrT> p_index, TNode<JSReceiver> p_value) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Smi> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<UintPtrT> tmp5;
  TNode<UintPtrT> tmp6;
  TNode<BoolT> tmp7;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp3 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_context, tmp2});
    tmp4 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp3});
    tmp5 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{p_index});
    tmp6 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp4});
    tmp7 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp5}, TNode<UintPtrT>{tmp6});
    ca_.Branch(tmp7, &block17, std::vector<Node*>{}, &block18, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<HeapObject> tmp11;
  TNode<IntPtrT> tmp12;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp9 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{p_index}, TNode<IntPtrT>{tmp8});
    tmp10 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{tmp9});
    std::tie(tmp11, tmp12) = NewReference_Object_0(state_, TNode<HeapObject>{p_context}, TNode<IntPtrT>{tmp10}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp11, tmp12}, p_value);
    ca_.Goto(&block20);
  }

  if (block18.is_used()) {
    ca_.Bind(&block18);
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block20);
}

void InitContextSlot_PromiseFinallyContext_PromiseFinallyContext_Constructor_Constructor_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<IntPtrT> p_index, TNode<JSReceiver> p_value) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Smi> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<UintPtrT> tmp5;
  TNode<UintPtrT> tmp6;
  TNode<BoolT> tmp7;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp3 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_context, tmp2});
    tmp4 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp3});
    tmp5 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{p_index});
    tmp6 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp4});
    tmp7 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp5}, TNode<UintPtrT>{tmp6});
    ca_.Branch(tmp7, &block17, std::vector<Node*>{}, &block18, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<HeapObject> tmp11;
  TNode<IntPtrT> tmp12;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp9 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{p_index}, TNode<IntPtrT>{tmp8});
    tmp10 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{tmp9});
    std::tie(tmp11, tmp12) = NewReference_Object_0(state_, TNode<HeapObject>{p_context}, TNode<IntPtrT>{tmp10}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp11, tmp12}, p_value);
    ca_.Goto(&block20);
  }

  if (block18.is_used()) {
    ca_.Bind(&block18);
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block20);
}

}  // namespace internal
}  // namespace v8

