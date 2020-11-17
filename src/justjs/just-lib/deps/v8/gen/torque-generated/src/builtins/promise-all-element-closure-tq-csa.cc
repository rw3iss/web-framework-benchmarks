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

TNode<IntPtrT> FromConstexpr_PromiseAllResolveElementContextSlots_constexpr_kPromiseAllResolveElementRemainingSlot_0(compiler::CodeAssemblerState* state_, PromiseBuiltins::PromiseAllResolveElementContextSlots p_o) {
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

TNode<IntPtrT> FromConstexpr_PromiseAllResolveElementContextSlots_constexpr_kPromiseAllResolveElementCapabilitySlot_0(compiler::CodeAssemblerState* state_, PromiseBuiltins::PromiseAllResolveElementContextSlots p_o) {
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

TNode<IntPtrT> FromConstexpr_PromiseAllResolveElementContextSlots_constexpr_kPromiseAllResolveElementValuesSlot_0(compiler::CodeAssemblerState* state_, PromiseBuiltins::PromiseAllResolveElementContextSlots p_o) {
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

TNode<IntPtrT> FromConstexpr_PromiseAllResolveElementContextSlots_constexpr_kPromiseAllResolveElementLength_0(compiler::CodeAssemblerState* state_, PromiseBuiltins::PromiseAllResolveElementContextSlots p_o) {
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

TNode<IntPtrT> kPromiseAllResolveElementRemainingSlot_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  TNode<IntPtrT> tmp0;
    tmp0 = FromConstexpr_PromiseAllResolveElementContextSlots_constexpr_kPromiseAllResolveElementRemainingSlot_0(state_, PromiseBuiltins::PromiseAllResolveElementContextSlots::kPromiseAllResolveElementRemainingSlot);
  TNode<IntPtrT> tmp1;
    tmp1 = (TNode<IntPtrT>{tmp0});
  return TNode<IntPtrT>{tmp1};
}

TNode<IntPtrT> kPromiseAllResolveElementCapabilitySlot_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  TNode<IntPtrT> tmp0;
    tmp0 = FromConstexpr_PromiseAllResolveElementContextSlots_constexpr_kPromiseAllResolveElementCapabilitySlot_0(state_, PromiseBuiltins::PromiseAllResolveElementContextSlots::kPromiseAllResolveElementCapabilitySlot);
  TNode<IntPtrT> tmp1;
    tmp1 = (TNode<IntPtrT>{tmp0});
  return TNode<IntPtrT>{tmp1};
}

TNode<IntPtrT> kPromiseAllResolveElementValuesSlot_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  TNode<IntPtrT> tmp0;
    tmp0 = FromConstexpr_PromiseAllResolveElementContextSlots_constexpr_kPromiseAllResolveElementValuesSlot_0(state_, PromiseBuiltins::PromiseAllResolveElementContextSlots::kPromiseAllResolveElementValuesSlot);
  TNode<IntPtrT> tmp1;
    tmp1 = (TNode<IntPtrT>{tmp0});
  return TNode<IntPtrT>{tmp1};
}

TF_BUILTIN(PromiseAllResolveElementClosure, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kReceiver));
USE(parameter1);
  TNode<JSFunction> parameter2 = UncheckedCast<JSFunction>(Parameter(Descriptor::kJSTarget));
USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::kValue));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Context> tmp0;
  TNode<Object> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = (TNode<Context>{parameter0});
    tmp1 = PromiseAllResolveElementClosure_PromiseAllWrapResultAsFulfilledFunctor_0(state_, TNode<Context>{tmp0}, TNode<Object>{parameter3}, TNode<JSFunction>{parameter2}, TorqueStructPromiseAllWrapResultAsFulfilledFunctor_0{}, false);
    CodeStubAssembler(state_).Return(tmp1);
  }
}

TF_BUILTIN(PromiseAllSettledResolveElementClosure, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kReceiver));
USE(parameter1);
  TNode<JSFunction> parameter2 = UncheckedCast<JSFunction>(Parameter(Descriptor::kJSTarget));
USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::kValue));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Context> tmp0;
  TNode<Object> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = (TNode<Context>{parameter0});
    tmp1 = PromiseAllResolveElementClosure_PromiseAllSettledWrapResultAsFulfilledFunctor_0(state_, TNode<Context>{tmp0}, TNode<Object>{parameter3}, TNode<JSFunction>{parameter2}, TorqueStructPromiseAllSettledWrapResultAsFulfilledFunctor_0{}, true);
    CodeStubAssembler(state_).Return(tmp1);
  }
}

TF_BUILTIN(PromiseAllSettledRejectElementClosure, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kReceiver));
USE(parameter1);
  TNode<JSFunction> parameter2 = UncheckedCast<JSFunction>(Parameter(Descriptor::kJSTarget));
USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::kValue));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Context> tmp0;
  TNode<Object> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = (TNode<Context>{parameter0});
    tmp1 = PromiseAllResolveElementClosure_PromiseAllSettledWrapResultAsRejectedFunctor_0(state_, TNode<Context>{tmp0}, TNode<Object>{parameter3}, TNode<JSFunction>{parameter2}, TorqueStructPromiseAllSettledWrapResultAsRejectedFunctor_0{}, true);
    CodeStubAssembler(state_).Return(tmp1);
  }
}

TNode<Object> PromiseAllResolveElementClosure_PromiseAllWrapResultAsFulfilledFunctor_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_value, TNode<JSFunction> p_function, TorqueStructPromiseAllWrapResultAsFulfilledFunctor_0 p_wrapResultFunctor, bool p_hasResolveAndRejectClosures) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block44(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<NativeContext> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_NativeContext_0(state_, TNode<HeapObject>{p_context}, &label1);
    ca_.Goto(&block4);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block5);
    }
  }

  TNode<NativeContext> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<IntPtrT> tmp4;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp2 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{ca_.UncheckedCast<Context>(p_context)});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    CodeStubAssembler(state_).StoreReference<Context>(CodeStubAssembler::Reference{p_function, tmp3}, tmp2);
    compiler::CodeAssemblerLabel label5(&ca_);
    tmp4 = CodeStubAssembler(state_).LoadJSReceiverIdentityHash(TNode<Object>{p_function}, &label5);
    ca_.Goto(&block16);
    if (label5.is_used()) {
      ca_.Bind(&label5);
      ca_.Goto(&block17);
    }
  }

  TNode<Oddball> tmp6;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp6 = Undefined_0(state_);
    ca_.Goto(&block1, tmp6);
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<HeapObject> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<Smi> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<HeapObject> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<FixedArray> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<BoolT> tmp20;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp8 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{tmp4}, TNode<IntPtrT>{tmp7});
    tmp9 = kPromiseAllResolveElementRemainingSlot_0(state_);
    std::tie(tmp10, tmp11) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_Smi_0(state_, TNode<Context>{ca_.UncheckedCast<Context>(p_context)}, TNode<IntPtrT>{tmp9}).Flatten();
    tmp12 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp10, tmp11});
    tmp13 = kPromiseAllResolveElementValuesSlot_0(state_);
    std::tie(tmp14, tmp15) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_FixedArray_0(state_, TNode<Context>{ca_.UncheckedCast<Context>(p_context)}, TNode<IntPtrT>{tmp13}).Flatten();
    tmp16 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{tmp14, tmp15});
    tmp17 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp18 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp8}, TNode<IntPtrT>{tmp17});
    tmp19 = CodeStubAssembler(state_).LoadAndUntagFixedArrayBaseLength(TNode<FixedArrayBase>{tmp16});
    tmp20 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp18}, TNode<IntPtrT>{tmp19});
    ca_.Branch(tmp20, &block22, std::vector<Node*>{}, &block23, std::vector<Node*>{tmp16});
  }

  TNode<IntPtrT> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<FixedArray> tmp23;
  TNode<IntPtrT> tmp24;
  TNode<HeapObject> tmp25;
  TNode<IntPtrT> tmp26;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    tmp21 = CodeStubAssembler(state_).LoadAndUntagFixedArrayBaseLength(TNode<FixedArrayBase>{tmp16});
    tmp22 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp23 = ExtractFixedArray_0(state_, TNode<FixedArray>{tmp16}, TNode<IntPtrT>{tmp22}, TNode<IntPtrT>{tmp21}, TNode<IntPtrT>{tmp18});
    tmp24 = kPromiseAllResolveElementValuesSlot_0(state_);
    std::tie(tmp25, tmp26) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_FixedArray_0(state_, TNode<Context>{ca_.UncheckedCast<Context>(p_context)}, TNode<IntPtrT>{tmp24}).Flatten();
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{tmp25, tmp26}, tmp23);
    ca_.Goto(&block23, tmp23);
  }

  TNode<FixedArray> phi_bb23_8;
  TNode<BoolT> tmp27;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_8);
    tmp27 = FromConstexpr_bool_constexpr_bool_0(state_, p_hasResolveAndRejectClosures);
    ca_.Branch(tmp27, &block24, std::vector<Node*>{}, &block25, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<Smi> tmp31;
  TNode<IntPtrT> tmp32;
  TNode<UintPtrT> tmp33;
  TNode<UintPtrT> tmp34;
  TNode<BoolT> tmp35;
  if (block24.is_used()) {
    ca_.Bind(&block24);
    tmp28 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp29 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp30 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp31 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{phi_bb23_8, tmp30});
    tmp32 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp31});
    tmp33 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp8});
    tmp34 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp32});
    tmp35 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp33}, TNode<UintPtrT>{tmp34});
    ca_.Branch(tmp35, &block32, std::vector<Node*>{}, &block33, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<IntPtrT> tmp38;
  TNode<HeapObject> tmp39;
  TNode<IntPtrT> tmp40;
  TNode<Object> tmp41;
  TNode<Oddball> tmp42;
  TNode<BoolT> tmp43;
  if (block32.is_used()) {
    ca_.Bind(&block32);
    tmp36 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp37 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp8}, TNode<IntPtrT>{tmp36});
    tmp38 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp28}, TNode<IntPtrT>{tmp37});
    std::tie(tmp39, tmp40) = NewReference_Object_0(state_, TNode<HeapObject>{phi_bb23_8}, TNode<IntPtrT>{tmp38}).Flatten();
    tmp41 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp39, tmp40});
    tmp42 = TheHole_0(state_);
    tmp43 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{tmp41}, TNode<HeapObject>{tmp42});
    ca_.Branch(tmp43, &block26, std::vector<Node*>{}, &block27, std::vector<Node*>{});
  }

  if (block33.is_used()) {
    ca_.Bind(&block33);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Oddball> tmp44;
  if (block26.is_used()) {
    ca_.Bind(&block26);
    tmp44 = Undefined_0(state_);
    ca_.Goto(&block1, tmp44);
  }

  if (block27.is_used()) {
    ca_.Bind(&block27);
    ca_.Goto(&block25);
  }

  TNode<IntPtrT> tmp45;
  TNode<IntPtrT> tmp46;
  TNode<IntPtrT> tmp47;
  TNode<Smi> tmp48;
  TNode<IntPtrT> tmp49;
  TNode<UintPtrT> tmp50;
  TNode<UintPtrT> tmp51;
  TNode<BoolT> tmp52;
  if (block25.is_used()) {
    ca_.Bind(&block25);
    tmp45 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp46 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp47 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp48 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{phi_bb23_8, tmp47});
    tmp49 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp48});
    tmp50 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp8});
    tmp51 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp49});
    tmp52 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp50}, TNode<UintPtrT>{tmp51});
    ca_.Branch(tmp52, &block40, std::vector<Node*>{}, &block41, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp53;
  TNode<IntPtrT> tmp54;
  TNode<IntPtrT> tmp55;
  TNode<HeapObject> tmp56;
  TNode<IntPtrT> tmp57;
  TNode<Smi> tmp58;
  TNode<Smi> tmp59;
  TNode<Smi> tmp60;
  TNode<BoolT> tmp61;
  if (block40.is_used()) {
    ca_.Bind(&block40);
    tmp53 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp54 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp8}, TNode<IntPtrT>{tmp53});
    tmp55 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp45}, TNode<IntPtrT>{tmp54});
    std::tie(tmp56, tmp57) = NewReference_Object_0(state_, TNode<HeapObject>{phi_bb23_8}, TNode<IntPtrT>{tmp55}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp56, tmp57}, p_value);
    tmp58 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp59 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp12}, TNode<Smi>{tmp58});
    tmp60 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp61 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp59}, TNode<Smi>{tmp60});
    ca_.Branch(tmp61, &block43, std::vector<Node*>{}, &block44, std::vector<Node*>{});
  }

  if (block41.is_used()) {
    ca_.Bind(&block41);
    CodeStubAssembler(state_).Unreachable();
  }

  if (block44.is_used()) {
    ca_.Bind(&block44);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/promise-all-element-closure.tq", 162});
      CodeStubAssembler(state_).FailAssert("Torque assert 'remainingElementsCount >= 0' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp62;
  TNode<HeapObject> tmp63;
  TNode<IntPtrT> tmp64;
  TNode<Smi> tmp65;
  TNode<BoolT> tmp66;
  if (block43.is_used()) {
    ca_.Bind(&block43);
    tmp62 = kPromiseAllResolveElementRemainingSlot_0(state_);
    std::tie(tmp63, tmp64) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_Smi_0(state_, TNode<Context>{ca_.UncheckedCast<Context>(p_context)}, TNode<IntPtrT>{tmp62}).Flatten();
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp63, tmp64}, tmp59);
    tmp65 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp66 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp59}, TNode<Smi>{tmp65});
    ca_.Branch(tmp66, &block45, std::vector<Node*>{}, &block46, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp67;
  TNode<HeapObject> tmp68;
  TNode<IntPtrT> tmp69;
  TNode<PromiseCapability> tmp70;
  TNode<IntPtrT> tmp71;
  TNode<Object> tmp72;
  TNode<Object> tmp73;
  TNode<IntPtrT> tmp74;
  TNode<HeapObject> tmp75;
  TNode<IntPtrT> tmp76;
  TNode<Map> tmp77;
  TNode<JSArray> tmp78;
  TNode<Oddball> tmp79;
  TNode<Object> tmp80;
  if (block45.is_used()) {
    ca_.Bind(&block45);
    tmp67 = kPromiseAllResolveElementCapabilitySlot_0(state_);
    std::tie(tmp68, tmp69) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_PromiseCapability_0(state_, TNode<Context>{ca_.UncheckedCast<Context>(p_context)}, TNode<IntPtrT>{tmp67}).Flatten();
    tmp70 = CodeStubAssembler(state_).LoadReference<PromiseCapability>(CodeStubAssembler::Reference{tmp68, tmp69});
    tmp71 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp72 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp70, tmp71});
    tmp73 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp72});
    tmp74 = JS_ARRAY_PACKED_ELEMENTS_MAP_INDEX_0(state_);
    std::tie(tmp75, tmp76) = NativeContextSlot_Map_0(state_, TNode<NativeContext>{tmp2}, TNode<IntPtrT>{tmp74}).Flatten();
    tmp77 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp75, tmp76});
    tmp78 = NewJSArray_0(state_, TNode<Context>{p_context}, TNode<Map>{tmp77}, TNode<FixedArrayBase>{phi_bb23_8});
    tmp79 = Undefined_0(state_);
    tmp80 = CodeStubAssembler(state_).Call(TNode<Context>{ca_.UncheckedCast<Context>(p_context)}, TNode<Object>{tmp73}, TNode<Object>{tmp79}, TNode<Object>{tmp78});
    ca_.Goto(&block46);
  }

  TNode<Oddball> tmp81;
  if (block46.is_used()) {
    ca_.Bind(&block46);
    tmp81 = Undefined_0(state_);
    ca_.Goto(&block1, tmp81);
  }

  TNode<Object> phi_bb1_3;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_3);
    ca_.Goto(&block47, phi_bb1_3);
  }

  TNode<Object> phi_bb47_3;
    ca_.Bind(&block47, &phi_bb47_3);
  return TNode<Object>{phi_bb47_3};
}

TNode<Object> PromiseAllResolveElementClosure_PromiseAllSettledWrapResultAsFulfilledFunctor_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_value, TNode<JSFunction> p_function, TorqueStructPromiseAllSettledWrapResultAsFulfilledFunctor_0 p_wrapResultFunctor, bool p_hasResolveAndRejectClosures) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block44(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<NativeContext> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_NativeContext_0(state_, TNode<HeapObject>{p_context}, &label1);
    ca_.Goto(&block4);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block5);
    }
  }

  TNode<NativeContext> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<IntPtrT> tmp4;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp2 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{ca_.UncheckedCast<Context>(p_context)});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    CodeStubAssembler(state_).StoreReference<Context>(CodeStubAssembler::Reference{p_function, tmp3}, tmp2);
    compiler::CodeAssemblerLabel label5(&ca_);
    tmp4 = CodeStubAssembler(state_).LoadJSReceiverIdentityHash(TNode<Object>{p_function}, &label5);
    ca_.Goto(&block16);
    if (label5.is_used()) {
      ca_.Bind(&label5);
      ca_.Goto(&block17);
    }
  }

  TNode<Oddball> tmp6;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp6 = Undefined_0(state_);
    ca_.Goto(&block1, tmp6);
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<HeapObject> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<Smi> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<HeapObject> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<FixedArray> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<BoolT> tmp20;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp8 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{tmp4}, TNode<IntPtrT>{tmp7});
    tmp9 = kPromiseAllResolveElementRemainingSlot_0(state_);
    std::tie(tmp10, tmp11) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_Smi_0(state_, TNode<Context>{ca_.UncheckedCast<Context>(p_context)}, TNode<IntPtrT>{tmp9}).Flatten();
    tmp12 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp10, tmp11});
    tmp13 = kPromiseAllResolveElementValuesSlot_0(state_);
    std::tie(tmp14, tmp15) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_FixedArray_0(state_, TNode<Context>{ca_.UncheckedCast<Context>(p_context)}, TNode<IntPtrT>{tmp13}).Flatten();
    tmp16 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{tmp14, tmp15});
    tmp17 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp18 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp8}, TNode<IntPtrT>{tmp17});
    tmp19 = CodeStubAssembler(state_).LoadAndUntagFixedArrayBaseLength(TNode<FixedArrayBase>{tmp16});
    tmp20 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp18}, TNode<IntPtrT>{tmp19});
    ca_.Branch(tmp20, &block22, std::vector<Node*>{}, &block23, std::vector<Node*>{tmp16});
  }

  TNode<IntPtrT> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<FixedArray> tmp23;
  TNode<IntPtrT> tmp24;
  TNode<HeapObject> tmp25;
  TNode<IntPtrT> tmp26;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    tmp21 = CodeStubAssembler(state_).LoadAndUntagFixedArrayBaseLength(TNode<FixedArrayBase>{tmp16});
    tmp22 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp23 = ExtractFixedArray_0(state_, TNode<FixedArray>{tmp16}, TNode<IntPtrT>{tmp22}, TNode<IntPtrT>{tmp21}, TNode<IntPtrT>{tmp18});
    tmp24 = kPromiseAllResolveElementValuesSlot_0(state_);
    std::tie(tmp25, tmp26) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_FixedArray_0(state_, TNode<Context>{ca_.UncheckedCast<Context>(p_context)}, TNode<IntPtrT>{tmp24}).Flatten();
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{tmp25, tmp26}, tmp23);
    ca_.Goto(&block23, tmp23);
  }

  TNode<FixedArray> phi_bb23_8;
  TNode<BoolT> tmp27;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_8);
    tmp27 = FromConstexpr_bool_constexpr_bool_0(state_, p_hasResolveAndRejectClosures);
    ca_.Branch(tmp27, &block24, std::vector<Node*>{}, &block25, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<Smi> tmp31;
  TNode<IntPtrT> tmp32;
  TNode<UintPtrT> tmp33;
  TNode<UintPtrT> tmp34;
  TNode<BoolT> tmp35;
  if (block24.is_used()) {
    ca_.Bind(&block24);
    tmp28 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp29 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp30 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp31 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{phi_bb23_8, tmp30});
    tmp32 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp31});
    tmp33 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp8});
    tmp34 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp32});
    tmp35 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp33}, TNode<UintPtrT>{tmp34});
    ca_.Branch(tmp35, &block32, std::vector<Node*>{}, &block33, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<IntPtrT> tmp38;
  TNode<HeapObject> tmp39;
  TNode<IntPtrT> tmp40;
  TNode<Object> tmp41;
  TNode<Oddball> tmp42;
  TNode<BoolT> tmp43;
  if (block32.is_used()) {
    ca_.Bind(&block32);
    tmp36 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp37 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp8}, TNode<IntPtrT>{tmp36});
    tmp38 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp28}, TNode<IntPtrT>{tmp37});
    std::tie(tmp39, tmp40) = NewReference_Object_0(state_, TNode<HeapObject>{phi_bb23_8}, TNode<IntPtrT>{tmp38}).Flatten();
    tmp41 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp39, tmp40});
    tmp42 = TheHole_0(state_);
    tmp43 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{tmp41}, TNode<HeapObject>{tmp42});
    ca_.Branch(tmp43, &block26, std::vector<Node*>{}, &block27, std::vector<Node*>{});
  }

  if (block33.is_used()) {
    ca_.Bind(&block33);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Oddball> tmp44;
  if (block26.is_used()) {
    ca_.Bind(&block26);
    tmp44 = Undefined_0(state_);
    ca_.Goto(&block1, tmp44);
  }

  if (block27.is_used()) {
    ca_.Bind(&block27);
    ca_.Goto(&block25);
  }

  TNode<IntPtrT> tmp45;
  TNode<HeapObject> tmp46;
  TNode<IntPtrT> tmp47;
  TNode<JSFunction> tmp48;
  TNode<IntPtrT> tmp49;
  TNode<HeapObject> tmp50;
  TNode<Map> tmp51;
  TNode<JSObject> tmp52;
  TNode<String> tmp53;
  TNode<String> tmp54;
  TNode<Object> tmp55;
  TNode<String> tmp56;
  TNode<Object> tmp57;
  TNode<IntPtrT> tmp58;
  TNode<IntPtrT> tmp59;
  TNode<IntPtrT> tmp60;
  TNode<Smi> tmp61;
  TNode<IntPtrT> tmp62;
  TNode<UintPtrT> tmp63;
  TNode<UintPtrT> tmp64;
  TNode<BoolT> tmp65;
  if (block25.is_used()) {
    ca_.Bind(&block25);
    tmp45 = OBJECT_FUNCTION_INDEX_0(state_);
    std::tie(tmp46, tmp47) = NativeContextSlot_JSFunction_0(state_, TNode<NativeContext>{tmp2}, TNode<IntPtrT>{tmp45}).Flatten();
    tmp48 = CodeStubAssembler(state_).LoadReference<JSFunction>(CodeStubAssembler::Reference{tmp46, tmp47});
    tmp49 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    tmp50 = CodeStubAssembler(state_).LoadReference<HeapObject>(CodeStubAssembler::Reference{tmp48, tmp49});
    tmp51 = UnsafeCast_Map_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp50});
    tmp52 = CodeStubAssembler(state_).AllocateJSObjectFromMap(TNode<Map>{tmp51});
    tmp53 = CodeStubAssembler(state_).StringConstant("status");
    tmp54 = CodeStubAssembler(state_).StringConstant("fulfilled");
    tmp55 = CodeStubAssembler(state_).CallBuiltin(Builtins::kFastCreateDataProperty, p_context, tmp52, tmp53, tmp54);
    tmp56 = CodeStubAssembler(state_).StringConstant("value");
    tmp57 = CodeStubAssembler(state_).CallBuiltin(Builtins::kFastCreateDataProperty, p_context, tmp52, tmp56, p_value);
    tmp58 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp59 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp60 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp61 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{phi_bb23_8, tmp60});
    tmp62 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp61});
    tmp63 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp8});
    tmp64 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp62});
    tmp65 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp63}, TNode<UintPtrT>{tmp64});
    ca_.Branch(tmp65, &block40, std::vector<Node*>{}, &block41, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp66;
  TNode<IntPtrT> tmp67;
  TNode<IntPtrT> tmp68;
  TNode<HeapObject> tmp69;
  TNode<IntPtrT> tmp70;
  TNode<Smi> tmp71;
  TNode<Smi> tmp72;
  TNode<Smi> tmp73;
  TNode<BoolT> tmp74;
  if (block40.is_used()) {
    ca_.Bind(&block40);
    tmp66 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp67 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp8}, TNode<IntPtrT>{tmp66});
    tmp68 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp58}, TNode<IntPtrT>{tmp67});
    std::tie(tmp69, tmp70) = NewReference_Object_0(state_, TNode<HeapObject>{phi_bb23_8}, TNode<IntPtrT>{tmp68}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp69, tmp70}, tmp52);
    tmp71 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp72 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp12}, TNode<Smi>{tmp71});
    tmp73 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp74 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp72}, TNode<Smi>{tmp73});
    ca_.Branch(tmp74, &block43, std::vector<Node*>{}, &block44, std::vector<Node*>{});
  }

  if (block41.is_used()) {
    ca_.Bind(&block41);
    CodeStubAssembler(state_).Unreachable();
  }

  if (block44.is_used()) {
    ca_.Bind(&block44);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/promise-all-element-closure.tq", 162});
      CodeStubAssembler(state_).FailAssert("Torque assert 'remainingElementsCount >= 0' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp75;
  TNode<HeapObject> tmp76;
  TNode<IntPtrT> tmp77;
  TNode<Smi> tmp78;
  TNode<BoolT> tmp79;
  if (block43.is_used()) {
    ca_.Bind(&block43);
    tmp75 = kPromiseAllResolveElementRemainingSlot_0(state_);
    std::tie(tmp76, tmp77) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_Smi_0(state_, TNode<Context>{ca_.UncheckedCast<Context>(p_context)}, TNode<IntPtrT>{tmp75}).Flatten();
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp76, tmp77}, tmp72);
    tmp78 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp79 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp72}, TNode<Smi>{tmp78});
    ca_.Branch(tmp79, &block45, std::vector<Node*>{}, &block46, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp80;
  TNode<HeapObject> tmp81;
  TNode<IntPtrT> tmp82;
  TNode<PromiseCapability> tmp83;
  TNode<IntPtrT> tmp84;
  TNode<Object> tmp85;
  TNode<Object> tmp86;
  TNode<IntPtrT> tmp87;
  TNode<HeapObject> tmp88;
  TNode<IntPtrT> tmp89;
  TNode<Map> tmp90;
  TNode<JSArray> tmp91;
  TNode<Oddball> tmp92;
  TNode<Object> tmp93;
  if (block45.is_used()) {
    ca_.Bind(&block45);
    tmp80 = kPromiseAllResolveElementCapabilitySlot_0(state_);
    std::tie(tmp81, tmp82) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_PromiseCapability_0(state_, TNode<Context>{ca_.UncheckedCast<Context>(p_context)}, TNode<IntPtrT>{tmp80}).Flatten();
    tmp83 = CodeStubAssembler(state_).LoadReference<PromiseCapability>(CodeStubAssembler::Reference{tmp81, tmp82});
    tmp84 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp85 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp83, tmp84});
    tmp86 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp85});
    tmp87 = JS_ARRAY_PACKED_ELEMENTS_MAP_INDEX_0(state_);
    std::tie(tmp88, tmp89) = NativeContextSlot_Map_0(state_, TNode<NativeContext>{tmp2}, TNode<IntPtrT>{tmp87}).Flatten();
    tmp90 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp88, tmp89});
    tmp91 = NewJSArray_0(state_, TNode<Context>{p_context}, TNode<Map>{tmp90}, TNode<FixedArrayBase>{phi_bb23_8});
    tmp92 = Undefined_0(state_);
    tmp93 = CodeStubAssembler(state_).Call(TNode<Context>{ca_.UncheckedCast<Context>(p_context)}, TNode<Object>{tmp86}, TNode<Object>{tmp92}, TNode<Object>{tmp91});
    ca_.Goto(&block46);
  }

  TNode<Oddball> tmp94;
  if (block46.is_used()) {
    ca_.Bind(&block46);
    tmp94 = Undefined_0(state_);
    ca_.Goto(&block1, tmp94);
  }

  TNode<Object> phi_bb1_3;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_3);
    ca_.Goto(&block47, phi_bb1_3);
  }

  TNode<Object> phi_bb47_3;
    ca_.Bind(&block47, &phi_bb47_3);
  return TNode<Object>{phi_bb47_3};
}

TNode<Object> PromiseAllResolveElementClosure_PromiseAllSettledWrapResultAsRejectedFunctor_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_value, TNode<JSFunction> p_function, TorqueStructPromiseAllSettledWrapResultAsRejectedFunctor_0 p_wrapResultFunctor, bool p_hasResolveAndRejectClosures) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block44(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<NativeContext> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_NativeContext_0(state_, TNode<HeapObject>{p_context}, &label1);
    ca_.Goto(&block4);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block5);
    }
  }

  TNode<NativeContext> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<IntPtrT> tmp4;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp2 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{ca_.UncheckedCast<Context>(p_context)});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    CodeStubAssembler(state_).StoreReference<Context>(CodeStubAssembler::Reference{p_function, tmp3}, tmp2);
    compiler::CodeAssemblerLabel label5(&ca_);
    tmp4 = CodeStubAssembler(state_).LoadJSReceiverIdentityHash(TNode<Object>{p_function}, &label5);
    ca_.Goto(&block16);
    if (label5.is_used()) {
      ca_.Bind(&label5);
      ca_.Goto(&block17);
    }
  }

  TNode<Oddball> tmp6;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp6 = Undefined_0(state_);
    ca_.Goto(&block1, tmp6);
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<HeapObject> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<Smi> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<HeapObject> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<FixedArray> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<BoolT> tmp20;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp8 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{tmp4}, TNode<IntPtrT>{tmp7});
    tmp9 = kPromiseAllResolveElementRemainingSlot_0(state_);
    std::tie(tmp10, tmp11) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_Smi_0(state_, TNode<Context>{ca_.UncheckedCast<Context>(p_context)}, TNode<IntPtrT>{tmp9}).Flatten();
    tmp12 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp10, tmp11});
    tmp13 = kPromiseAllResolveElementValuesSlot_0(state_);
    std::tie(tmp14, tmp15) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_FixedArray_0(state_, TNode<Context>{ca_.UncheckedCast<Context>(p_context)}, TNode<IntPtrT>{tmp13}).Flatten();
    tmp16 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{tmp14, tmp15});
    tmp17 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp18 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp8}, TNode<IntPtrT>{tmp17});
    tmp19 = CodeStubAssembler(state_).LoadAndUntagFixedArrayBaseLength(TNode<FixedArrayBase>{tmp16});
    tmp20 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp18}, TNode<IntPtrT>{tmp19});
    ca_.Branch(tmp20, &block22, std::vector<Node*>{}, &block23, std::vector<Node*>{tmp16});
  }

  TNode<IntPtrT> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<FixedArray> tmp23;
  TNode<IntPtrT> tmp24;
  TNode<HeapObject> tmp25;
  TNode<IntPtrT> tmp26;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    tmp21 = CodeStubAssembler(state_).LoadAndUntagFixedArrayBaseLength(TNode<FixedArrayBase>{tmp16});
    tmp22 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp23 = ExtractFixedArray_0(state_, TNode<FixedArray>{tmp16}, TNode<IntPtrT>{tmp22}, TNode<IntPtrT>{tmp21}, TNode<IntPtrT>{tmp18});
    tmp24 = kPromiseAllResolveElementValuesSlot_0(state_);
    std::tie(tmp25, tmp26) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_FixedArray_0(state_, TNode<Context>{ca_.UncheckedCast<Context>(p_context)}, TNode<IntPtrT>{tmp24}).Flatten();
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{tmp25, tmp26}, tmp23);
    ca_.Goto(&block23, tmp23);
  }

  TNode<FixedArray> phi_bb23_8;
  TNode<BoolT> tmp27;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_8);
    tmp27 = FromConstexpr_bool_constexpr_bool_0(state_, p_hasResolveAndRejectClosures);
    ca_.Branch(tmp27, &block24, std::vector<Node*>{}, &block25, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<Smi> tmp31;
  TNode<IntPtrT> tmp32;
  TNode<UintPtrT> tmp33;
  TNode<UintPtrT> tmp34;
  TNode<BoolT> tmp35;
  if (block24.is_used()) {
    ca_.Bind(&block24);
    tmp28 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp29 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp30 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp31 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{phi_bb23_8, tmp30});
    tmp32 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp31});
    tmp33 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp8});
    tmp34 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp32});
    tmp35 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp33}, TNode<UintPtrT>{tmp34});
    ca_.Branch(tmp35, &block32, std::vector<Node*>{}, &block33, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<IntPtrT> tmp38;
  TNode<HeapObject> tmp39;
  TNode<IntPtrT> tmp40;
  TNode<Object> tmp41;
  TNode<Oddball> tmp42;
  TNode<BoolT> tmp43;
  if (block32.is_used()) {
    ca_.Bind(&block32);
    tmp36 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp37 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp8}, TNode<IntPtrT>{tmp36});
    tmp38 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp28}, TNode<IntPtrT>{tmp37});
    std::tie(tmp39, tmp40) = NewReference_Object_0(state_, TNode<HeapObject>{phi_bb23_8}, TNode<IntPtrT>{tmp38}).Flatten();
    tmp41 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp39, tmp40});
    tmp42 = TheHole_0(state_);
    tmp43 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{tmp41}, TNode<HeapObject>{tmp42});
    ca_.Branch(tmp43, &block26, std::vector<Node*>{}, &block27, std::vector<Node*>{});
  }

  if (block33.is_used()) {
    ca_.Bind(&block33);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Oddball> tmp44;
  if (block26.is_used()) {
    ca_.Bind(&block26);
    tmp44 = Undefined_0(state_);
    ca_.Goto(&block1, tmp44);
  }

  if (block27.is_used()) {
    ca_.Bind(&block27);
    ca_.Goto(&block25);
  }

  TNode<IntPtrT> tmp45;
  TNode<HeapObject> tmp46;
  TNode<IntPtrT> tmp47;
  TNode<JSFunction> tmp48;
  TNode<IntPtrT> tmp49;
  TNode<HeapObject> tmp50;
  TNode<Map> tmp51;
  TNode<JSObject> tmp52;
  TNode<String> tmp53;
  TNode<String> tmp54;
  TNode<Object> tmp55;
  TNode<String> tmp56;
  TNode<Object> tmp57;
  TNode<IntPtrT> tmp58;
  TNode<IntPtrT> tmp59;
  TNode<IntPtrT> tmp60;
  TNode<Smi> tmp61;
  TNode<IntPtrT> tmp62;
  TNode<UintPtrT> tmp63;
  TNode<UintPtrT> tmp64;
  TNode<BoolT> tmp65;
  if (block25.is_used()) {
    ca_.Bind(&block25);
    tmp45 = OBJECT_FUNCTION_INDEX_0(state_);
    std::tie(tmp46, tmp47) = NativeContextSlot_JSFunction_0(state_, TNode<NativeContext>{tmp2}, TNode<IntPtrT>{tmp45}).Flatten();
    tmp48 = CodeStubAssembler(state_).LoadReference<JSFunction>(CodeStubAssembler::Reference{tmp46, tmp47});
    tmp49 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    tmp50 = CodeStubAssembler(state_).LoadReference<HeapObject>(CodeStubAssembler::Reference{tmp48, tmp49});
    tmp51 = UnsafeCast_Map_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp50});
    tmp52 = CodeStubAssembler(state_).AllocateJSObjectFromMap(TNode<Map>{tmp51});
    tmp53 = CodeStubAssembler(state_).StringConstant("status");
    tmp54 = CodeStubAssembler(state_).StringConstant("rejected");
    tmp55 = CodeStubAssembler(state_).CallBuiltin(Builtins::kFastCreateDataProperty, p_context, tmp52, tmp53, tmp54);
    tmp56 = CodeStubAssembler(state_).StringConstant("reason");
    tmp57 = CodeStubAssembler(state_).CallBuiltin(Builtins::kFastCreateDataProperty, p_context, tmp52, tmp56, p_value);
    tmp58 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp59 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp60 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp61 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{phi_bb23_8, tmp60});
    tmp62 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp61});
    tmp63 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp8});
    tmp64 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp62});
    tmp65 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp63}, TNode<UintPtrT>{tmp64});
    ca_.Branch(tmp65, &block40, std::vector<Node*>{}, &block41, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp66;
  TNode<IntPtrT> tmp67;
  TNode<IntPtrT> tmp68;
  TNode<HeapObject> tmp69;
  TNode<IntPtrT> tmp70;
  TNode<Smi> tmp71;
  TNode<Smi> tmp72;
  TNode<Smi> tmp73;
  TNode<BoolT> tmp74;
  if (block40.is_used()) {
    ca_.Bind(&block40);
    tmp66 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp67 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp8}, TNode<IntPtrT>{tmp66});
    tmp68 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp58}, TNode<IntPtrT>{tmp67});
    std::tie(tmp69, tmp70) = NewReference_Object_0(state_, TNode<HeapObject>{phi_bb23_8}, TNode<IntPtrT>{tmp68}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp69, tmp70}, tmp52);
    tmp71 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp72 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp12}, TNode<Smi>{tmp71});
    tmp73 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp74 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp72}, TNode<Smi>{tmp73});
    ca_.Branch(tmp74, &block43, std::vector<Node*>{}, &block44, std::vector<Node*>{});
  }

  if (block41.is_used()) {
    ca_.Bind(&block41);
    CodeStubAssembler(state_).Unreachable();
  }

  if (block44.is_used()) {
    ca_.Bind(&block44);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/promise-all-element-closure.tq", 162});
      CodeStubAssembler(state_).FailAssert("Torque assert 'remainingElementsCount >= 0' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp75;
  TNode<HeapObject> tmp76;
  TNode<IntPtrT> tmp77;
  TNode<Smi> tmp78;
  TNode<BoolT> tmp79;
  if (block43.is_used()) {
    ca_.Bind(&block43);
    tmp75 = kPromiseAllResolveElementRemainingSlot_0(state_);
    std::tie(tmp76, tmp77) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_Smi_0(state_, TNode<Context>{ca_.UncheckedCast<Context>(p_context)}, TNode<IntPtrT>{tmp75}).Flatten();
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp76, tmp77}, tmp72);
    tmp78 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp79 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp72}, TNode<Smi>{tmp78});
    ca_.Branch(tmp79, &block45, std::vector<Node*>{}, &block46, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp80;
  TNode<HeapObject> tmp81;
  TNode<IntPtrT> tmp82;
  TNode<PromiseCapability> tmp83;
  TNode<IntPtrT> tmp84;
  TNode<Object> tmp85;
  TNode<Object> tmp86;
  TNode<IntPtrT> tmp87;
  TNode<HeapObject> tmp88;
  TNode<IntPtrT> tmp89;
  TNode<Map> tmp90;
  TNode<JSArray> tmp91;
  TNode<Oddball> tmp92;
  TNode<Object> tmp93;
  if (block45.is_used()) {
    ca_.Bind(&block45);
    tmp80 = kPromiseAllResolveElementCapabilitySlot_0(state_);
    std::tie(tmp81, tmp82) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_PromiseCapability_0(state_, TNode<Context>{ca_.UncheckedCast<Context>(p_context)}, TNode<IntPtrT>{tmp80}).Flatten();
    tmp83 = CodeStubAssembler(state_).LoadReference<PromiseCapability>(CodeStubAssembler::Reference{tmp81, tmp82});
    tmp84 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp85 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp83, tmp84});
    tmp86 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp85});
    tmp87 = JS_ARRAY_PACKED_ELEMENTS_MAP_INDEX_0(state_);
    std::tie(tmp88, tmp89) = NativeContextSlot_Map_0(state_, TNode<NativeContext>{tmp2}, TNode<IntPtrT>{tmp87}).Flatten();
    tmp90 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp88, tmp89});
    tmp91 = NewJSArray_0(state_, TNode<Context>{p_context}, TNode<Map>{tmp90}, TNode<FixedArrayBase>{phi_bb23_8});
    tmp92 = Undefined_0(state_);
    tmp93 = CodeStubAssembler(state_).Call(TNode<Context>{ca_.UncheckedCast<Context>(p_context)}, TNode<Object>{tmp86}, TNode<Object>{tmp92}, TNode<Object>{tmp91});
    ca_.Goto(&block46);
  }

  TNode<Oddball> tmp94;
  if (block46.is_used()) {
    ca_.Bind(&block46);
    tmp94 = Undefined_0(state_);
    ca_.Goto(&block1, tmp94);
  }

  TNode<Object> phi_bb1_3;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_3);
    ca_.Goto(&block47, phi_bb1_3);
  }

  TNode<Object> phi_bb47_3;
    ca_.Bind(&block47, &phi_bb47_3);
  return TNode<Object>{phi_bb47_3};
}

TorqueStructReference_Smi_0 ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_Smi_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<IntPtrT> p_index) {
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
    std::tie(tmp13, tmp14) = ReferenceCast_Smi_Object_0(state_, TorqueStructReference_Object_0{TNode<HeapObject>{tmp11}, TNode<IntPtrT>{tmp12}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Goto(&block9);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block9);
  return TorqueStructReference_Smi_0{TNode<HeapObject>{tmp13}, TNode<IntPtrT>{tmp14}, TorqueStructUnsafe_0{}};
}

TorqueStructReference_FixedArray_0 ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_FixedArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<IntPtrT> p_index) {
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
    std::tie(tmp13, tmp14) = ReferenceCast_FixedArray_Object_0(state_, TorqueStructReference_Object_0{TNode<HeapObject>{tmp11}, TNode<IntPtrT>{tmp12}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Goto(&block9);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block9);
  return TorqueStructReference_FixedArray_0{TNode<HeapObject>{tmp13}, TNode<IntPtrT>{tmp14}, TorqueStructUnsafe_0{}};
}

TorqueStructReference_PromiseCapability_0 ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_PromiseCapability_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<IntPtrT> p_index) {
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
    std::tie(tmp13, tmp14) = ReferenceCast_PromiseCapability_Object_0(state_, TorqueStructReference_Object_0{TNode<HeapObject>{tmp11}, TNode<IntPtrT>{tmp12}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Goto(&block9);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block9);
  return TorqueStructReference_PromiseCapability_0{TNode<HeapObject>{tmp13}, TNode<IntPtrT>{tmp14}, TorqueStructUnsafe_0{}};
}

}  // namespace internal
}  // namespace v8

