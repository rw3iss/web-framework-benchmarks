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

TNode<String> kConstructorString_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  TNode<String> tmp0;
    tmp0 = CodeStubAssembler(state_).ConstructorStringConstant();
  return TNode<String>{tmp0};
}

TF_BUILTIN(PromiseResolveTrampoline, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kReceiver));
USE(parameter1);
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::kValue));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
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
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, MessageTemplate::kCalledOnNonObject, "PromiseResolve");
  }

  TNode<Object> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = CodeStubAssembler(state_).CallBuiltin(Builtins::kPromiseResolve, parameter0, tmp0, parameter2);
    CodeStubAssembler(state_).Return(tmp2);
  }
}

TF_BUILTIN(PromiseResolve, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedCast<JSReceiver>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    ca_.Goto(&block0);

  TNode<NativeContext> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<HeapObject> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<JSFunction> tmp4;
  TNode<JSPromise> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{parameter0});
    tmp1 = PROMISE_FUNCTION_INDEX_0(state_);
    std::tie(tmp2, tmp3) = NativeContextSlot_Context_JSFunction_0(state_, TNode<Context>{parameter0}, TNode<IntPtrT>{tmp1}).Flatten();
    tmp4 = CodeStubAssembler(state_).LoadReference<JSFunction>(CodeStubAssembler::Reference{tmp2, tmp3});
    compiler::CodeAssemblerLabel label6(&ca_);
    tmp5 = Cast_JSPromise_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2}, &label6);
    ca_.Goto(&block5);
    if (label6.is_used()) {
      ca_.Bind(&label6);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block2);
  }

  TNode<IntPtrT> tmp7;
  TNode<HeapObject> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<JSObject> tmp10;
  TNode<NativeContext> tmp11;
  TNode<BoolT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<Map> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<HeapObject> tmp16;
  TNode<BoolT> tmp17;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp7 = PROMISE_PROTOTYPE_INDEX_0(state_);
    std::tie(tmp8, tmp9) = NativeContextSlot_Context_JSObject_0(state_, TNode<Context>{parameter0}, TNode<IntPtrT>{tmp7}).Flatten();
    tmp10 = CodeStubAssembler(state_).LoadReference<JSObject>(CodeStubAssembler::Reference{tmp8, tmp9});
    tmp11 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{parameter0});
    tmp12 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp0}, TNode<HeapObject>{tmp11});
    CodeStubAssembler(state_).StaticAssert(TNode<BoolT>{tmp12}, "static_assert(nativeContext == LoadNativeContext(context)) at src/builtins/promise-resolve.tq:45:5");
    tmp13 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp14 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp5, tmp13});
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    tmp16 = CodeStubAssembler(state_).LoadReference<HeapObject>(CodeStubAssembler::Reference{tmp14, tmp15});
    tmp17 = CodeStubAssembler(state_).TaggedNotEqual(TNode<HeapObject>{tmp16}, TNode<HeapObject>{tmp10});
    ca_.Branch(tmp17, &block7, std::vector<Node*>{}, &block8, std::vector<Node*>{});
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    ca_.Goto(&block4);
  }

  TNode<BoolT> tmp18;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp18 = CodeStubAssembler(state_).IsPromiseSpeciesProtectorCellInvalid();
    ca_.Branch(tmp18, &block9, std::vector<Node*>{}, &block10, std::vector<Node*>{});
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    ca_.Goto(&block4);
  }

  TNode<BoolT> tmp19;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp19 = CodeStubAssembler(state_).TaggedNotEqual(TNode<HeapObject>{tmp4}, TNode<HeapObject>{parameter1});
    ca_.Branch(tmp19, &block11, std::vector<Node*>{}, &block12, std::vector<Node*>{});
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    ca_.Goto(&block4);
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    CodeStubAssembler(state_).Return(tmp5);
  }

  TNode<String> tmp20;
  TNode<Object> tmp21;
  TNode<BoolT> tmp22;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp20 = kConstructorString_0(state_);
    tmp21 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<Object>{parameter2}, TNode<Object>{tmp20});
    tmp22 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{tmp21}, TNode<HeapObject>{parameter1});
    ca_.Branch(tmp22, &block13, std::vector<Node*>{}, &block14, std::vector<Node*>{});
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    ca_.Goto(&block2);
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    CodeStubAssembler(state_).Return(parameter2);
  }

  TNode<BoolT> tmp23;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp23 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp4}, TNode<HeapObject>{parameter1});
    ca_.Branch(tmp23, &block15, std::vector<Node*>{}, &block16, std::vector<Node*>{});
  }

  TNode<JSPromise> tmp24;
  TNode<Object> tmp25;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp24 = NewJSPromise_1(state_, TNode<Context>{parameter0});
    tmp25 = CodeStubAssembler(state_).CallBuiltin(Builtins::kResolvePromise, parameter0, tmp24, parameter2);
    CodeStubAssembler(state_).Return(tmp24);
  }

  TNode<Oddball> tmp26;
  TNode<PromiseCapability> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<Object> tmp29;
  TNode<JSReceiver> tmp30;
  TNode<Oddball> tmp31;
  TNode<Object> tmp32;
  TNode<IntPtrT> tmp33;
  TNode<HeapObject> tmp34;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp26 = True_0(state_);
    tmp27 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kNewPromiseCapability, parameter0, parameter1, tmp26));
    tmp28 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp29 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp27, tmp28});
    tmp30 = UnsafeCast_Callable_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp29});
    tmp31 = Undefined_0(state_);
    tmp32 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<Object>{tmp30}, TNode<Object>{tmp31}, TNode<Object>{parameter2});
    tmp33 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp34 = CodeStubAssembler(state_).LoadReference<HeapObject>(CodeStubAssembler::Reference{tmp27, tmp33});
    CodeStubAssembler(state_).Return(tmp34);
  }
}

TNode<String> kThenString_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  TNode<String> tmp0;
    tmp0 = CodeStubAssembler(state_).ThenStringConstant();
  return TNode<String>{tmp0};
}

TF_BUILTIN(ResolvePromise, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSPromise> parameter1 = UncheckedCast<JSPromise>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block35(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = PromiseBuiltinsAssembler(state_).IsPromiseHookEnabledOrDebugIsActiveOrHasAsyncEventDelegate();
    ca_.Branch(tmp0, &block3, std::vector<Node*>{}, &block4, std::vector<Node*>{});
  }

  TNode<BoolT> tmp1;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp1 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block5, tmp1);
  }

  TNode<BoolT> tmp2;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp2 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{parameter1}, TNode<Object>{parameter2});
    ca_.Goto(&block5, tmp2);
  }

  TNode<BoolT> phi_bb5_4;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_4);
    ca_.Branch(phi_bb5_4, &block1, std::vector<Node*>{}, &block2, std::vector<Node*>{});
  }

  TNode<Object> tmp3;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = CodeStubAssembler(state_).CallRuntime(Runtime::kResolvePromise, parameter0, parameter1, parameter2); 
    CodeStubAssembler(state_).Return(tmp3);
  }

  TNode<Oddball> tmp4;
  TNode<BoolT> tmp5;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp4 = Undefined_0(state_);
    tmp5 = CodeStubAssembler(state_).TaggedIsSmi(TNode<Object>{parameter2});
    ca_.Branch(tmp5, &block10, std::vector<Node*>{}, &block11, std::vector<Node*>{});
  }

  TNode<Oddball> tmp6;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp6 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kFulfillPromise, parameter0, parameter1, parameter2));
    CodeStubAssembler(state_).Return(tmp6);
  }

  TNode<HeapObject> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Map> tmp9;
  TNode<BoolT> tmp10;
  TNode<BoolT> tmp11;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp7 = UnsafeCast_HeapObject_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2});
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp9 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp7, tmp8});
    tmp10 = CodeStubAssembler(state_).IsJSReceiverMap(TNode<Map>{tmp9});
    tmp11 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp10});
    ca_.Branch(tmp11, &block12, std::vector<Node*>{}, &block13, std::vector<Node*>{});
  }

  TNode<Oddball> tmp12;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp12 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kFulfillPromise, parameter0, parameter1, parameter2));
    CodeStubAssembler(state_).Return(tmp12);
  }

  TNode<BoolT> tmp13;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp13 = IsForceSlowPath_0(state_);
    ca_.Branch(tmp13, &block14, std::vector<Node*>{}, &block15, std::vector<Node*>{});
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    ca_.Goto(&block9);
  }

  TNode<BoolT> tmp14;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp14 = CodeStubAssembler(state_).IsPromiseThenProtectorCellInvalid();
    ca_.Branch(tmp14, &block16, std::vector<Node*>{}, &block17, std::vector<Node*>{});
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    ca_.Goto(&block9);
  }

  TNode<NativeContext> tmp15;
  TNode<BoolT> tmp16;
  TNode<BoolT> tmp17;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp15 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{parameter0});
    tmp16 = CodeStubAssembler(state_).IsJSPromiseMap(TNode<Map>{tmp9});
    tmp17 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp16});
    ca_.Branch(tmp17, &block18, std::vector<Node*>{}, &block19, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp18;
  TNode<HeapObject> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<Map> tmp21;
  TNode<BoolT> tmp22;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp18 = ITERATOR_RESULT_MAP_INDEX_0(state_);
    std::tie(tmp19, tmp20) = NativeContextSlot_Context_Map_0(state_, TNode<Context>{parameter0}, TNode<IntPtrT>{tmp18}).Flatten();
    tmp21 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp19, tmp20});
    tmp22 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp9}, TNode<HeapObject>{tmp21});
    ca_.Branch(tmp22, &block28, std::vector<Node*>{}, &block29, std::vector<Node*>{});
  }

  TNode<Oddball> tmp23;
  if (block28.is_used()) {
    ca_.Bind(&block28);
    tmp23 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kFulfillPromise, parameter0, parameter1, parameter2));
    CodeStubAssembler(state_).Return(tmp23);
  }

  if (block29.is_used()) {
    ca_.Bind(&block29);
    ca_.Goto(&block9);
  }

  TNode<IntPtrT> tmp24;
  TNode<HeapObject> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<JSObject> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<HeapObject> tmp29;
  TNode<BoolT> tmp30;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp24 = PROMISE_PROTOTYPE_INDEX_0(state_);
    std::tie(tmp25, tmp26) = NativeContextSlot_Context_JSObject_0(state_, TNode<Context>{parameter0}, TNode<IntPtrT>{tmp24}).Flatten();
    tmp27 = CodeStubAssembler(state_).LoadReference<JSObject>(CodeStubAssembler::Reference{tmp25, tmp26});
    tmp28 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    tmp29 = CodeStubAssembler(state_).LoadReference<HeapObject>(CodeStubAssembler::Reference{tmp9, tmp28});
    tmp30 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp29}, TNode<HeapObject>{tmp27});
    ca_.Branch(tmp30, &block31, std::vector<Node*>{}, &block32, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp31;
  TNode<HeapObject> tmp32;
  TNode<IntPtrT> tmp33;
  TNode<JSFunction> tmp34;
  TNode<NativeContext> tmp35;
  TNode<BoolT> tmp36;
  if (block31.is_used()) {
    ca_.Bind(&block31);
    tmp31 = PROMISE_THEN_INDEX_0(state_);
    std::tie(tmp32, tmp33) = NativeContextSlot_Context_JSFunction_0(state_, TNode<Context>{parameter0}, TNode<IntPtrT>{tmp31}).Flatten();
    tmp34 = CodeStubAssembler(state_).LoadReference<JSFunction>(CodeStubAssembler::Reference{tmp32, tmp33});
    tmp35 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{parameter0});
    tmp36 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp15}, TNode<HeapObject>{tmp35});
    CodeStubAssembler(state_).StaticAssert(TNode<BoolT>{tmp36}, "static_assert(nativeContext == LoadNativeContext(context)) at src/builtins/promise-resolve.tq:155:7");
    ca_.Goto(&block7, tmp34);
  }

  if (block32.is_used()) {
    ca_.Bind(&block32);
    ca_.Goto(&block9);
  }

  TNode<String> tmp37;
  TNode<Object> tmp38;
      TNode<Object> tmp40;
  TNode<BoolT> tmp41;
  TNode<BoolT> tmp42;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp37 = kThenString_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch39__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch39__label);
    tmp38 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<Object>{parameter2}, TNode<Object>{tmp37});
    }
    if (catch39__label.is_used()) {
      compiler::CodeAssemblerLabel catch39_skip(&ca_);
      ca_.Goto(&catch39_skip);
      ca_.Bind(&catch39__label, &tmp40);
      ca_.Goto(&block35);
      ca_.Bind(&catch39_skip);
    }
    tmp41 = Is_Callable_Object_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp38});
    tmp42 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp41});
    ca_.Branch(tmp42, &block36, std::vector<Node*>{}, &block37, std::vector<Node*>{});
  }

  TNode<Oddball> tmp43;
  TNode<Object> tmp44;
  if (block35.is_used()) {
    ca_.Bind(&block35);
    tmp43 = False_0(state_);
    tmp44 = CodeStubAssembler(state_).CallBuiltin(Builtins::kRejectPromise, parameter0, parameter1, tmp40, tmp43);
    CodeStubAssembler(state_).Return(tmp44);
  }

  TNode<Oddball> tmp45;
  if (block36.is_used()) {
    ca_.Bind(&block36);
    tmp45 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kFulfillPromise, parameter0, parameter1, parameter2));
    CodeStubAssembler(state_).Return(tmp45);
  }

  if (block37.is_used()) {
    ca_.Bind(&block37);
    ca_.Goto(&block7, tmp38);
  }

  TNode<Object> phi_bb7_3;
  TNode<JSReceiver> tmp46;
  TNode<JSReceiver> tmp47;
  TNode<PromiseResolveThenableJobTask> tmp48;
  TNode<IntPtrT> tmp49;
  TNode<Context> tmp50;
  TNode<Oddball> tmp51;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_3);
    tmp46 = UnsafeCast_JSReceiver_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2});
    tmp47 = UnsafeCast_Callable_0(state_, TNode<Context>{parameter0}, TNode<Object>{phi_bb7_3});
    tmp48 = NewPromiseResolveThenableJobTask_0(state_, TNode<Context>{parameter0}, TNode<JSPromise>{parameter1}, TNode<JSReceiver>{tmp46}, TNode<JSReceiver>{tmp47});
    tmp49 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp50 = CodeStubAssembler(state_).LoadReference<Context>(CodeStubAssembler::Reference{tmp48, tmp49});
    tmp51 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kEnqueueMicrotask, tmp50, tmp48));
    CodeStubAssembler(state_).Return(tmp51);
  }
}

TNode<JSPromise> Cast_JSPromise_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError) {
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

  TNode<JSPromise> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_JSPromise_0(state_, TNode<HeapObject>{tmp0}, &label3);
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
  return TNode<JSPromise>{tmp2};
}

TorqueStructReference_JSObject_0 NativeContextSlot_Context_JSObject_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<IntPtrT> p_index) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<HeapObject> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1) = NativeContextSlot_JSObject_1(state_, TNode<Context>{p_context}, TNode<IntPtrT>{p_index}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_JSObject_0{TNode<HeapObject>{tmp0}, TNode<IntPtrT>{tmp1}, TorqueStructUnsafe_0{}};
}

}  // namespace internal
}  // namespace v8

