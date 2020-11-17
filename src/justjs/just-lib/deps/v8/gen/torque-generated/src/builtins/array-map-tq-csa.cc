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

TF_BUILTIN(ArrayMapPreLoopLazyDeoptContinuation, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kReceiver));
USE(parameter1);
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::kCallback));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::kThisArg));
  USE(parameter3);
  TNode<Object> parameter4 = UncheckedCast<Object>(Parameter(Descriptor::kLength));
  USE(parameter4);
  TNode<Object> parameter5 = UncheckedCast<Object>(Parameter(Descriptor::kResult));
  USE(parameter5);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
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
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSReceiver> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter5}, &label3);
    ca_.Goto(&block7);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block8);
    }
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Number> tmp4;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    compiler::CodeAssemblerLabel label5(&ca_);
    tmp4 = Cast_Number_0(state_, TNode<Object>{parameter4}, &label5);
    ca_.Goto(&block11);
    if (label5.is_used()) {
      ca_.Bind(&label5);
      ca_.Goto(&block12);
    }
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSReceiver> tmp6;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    compiler::CodeAssemblerLabel label7(&ca_);
    tmp6 = Cast_Callable_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2}, &label7);
    ca_.Goto(&block15);
    if (label7.is_used()) {
      ca_.Bind(&label7);
      ca_.Goto(&block16);
    }
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, MessageTemplate::kCalledNonCallable, TNode<Object>{parameter2});
  }

  TNode<Smi> tmp8;
  TNode<Object> tmp9;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp8 = kZero_0(state_);
    tmp9 = CodeStubAssembler(state_).CallBuiltin(Builtins::kArrayMapLoopContinuation, parameter0, tmp0, tmp6, parameter3, tmp2, tmp0, tmp8, tmp4);
    CodeStubAssembler(state_).Return(tmp9);
  }
}

TF_BUILTIN(ArrayMapLoopEagerDeoptContinuation, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kReceiver));
USE(parameter1);
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::kCallback));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::kThisArg));
  USE(parameter3);
  TNode<Object> parameter4 = UncheckedCast<Object>(Parameter(Descriptor::kArray));
  USE(parameter4);
  TNode<Object> parameter5 = UncheckedCast<Object>(Parameter(Descriptor::kInitialK));
  USE(parameter5);
  TNode<Object> parameter6 = UncheckedCast<Object>(Parameter(Descriptor::kLength));
  USE(parameter6);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
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
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSReceiver> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_Callable_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2}, &label3);
    ca_.Goto(&block7);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block8);
    }
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSReceiver> tmp4;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    compiler::CodeAssemblerLabel label5(&ca_);
    tmp4 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter4}, &label5);
    ca_.Goto(&block11);
    if (label5.is_used()) {
      ca_.Bind(&label5);
      ca_.Goto(&block12);
    }
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Number> tmp6;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    compiler::CodeAssemblerLabel label7(&ca_);
    tmp6 = Cast_Number_0(state_, TNode<Object>{parameter5}, &label7);
    ca_.Goto(&block15);
    if (label7.is_used()) {
      ca_.Bind(&label7);
      ca_.Goto(&block16);
    }
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Number> tmp8;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    compiler::CodeAssemblerLabel label9(&ca_);
    tmp8 = Cast_Number_0(state_, TNode<Object>{parameter6}, &label9);
    ca_.Goto(&block19);
    if (label9.is_used()) {
      ca_.Bind(&label9);
      ca_.Goto(&block20);
    }
  }

  if (block20.is_used()) {
    ca_.Bind(&block20);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Object> tmp10;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp10 = CodeStubAssembler(state_).CallBuiltin(Builtins::kArrayMapLoopContinuation, parameter0, tmp0, tmp2, parameter3, tmp4, tmp0, tmp6, tmp8);
    CodeStubAssembler(state_).Return(tmp10);
  }
}

TF_BUILTIN(ArrayMapLoopLazyDeoptContinuation, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kReceiver));
USE(parameter1);
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::kCallback));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::kThisArg));
  USE(parameter3);
  TNode<Object> parameter4 = UncheckedCast<Object>(Parameter(Descriptor::kArray));
  USE(parameter4);
  TNode<Object> parameter5 = UncheckedCast<Object>(Parameter(Descriptor::kInitialK));
  USE(parameter5);
  TNode<Object> parameter6 = UncheckedCast<Object>(Parameter(Descriptor::kLength));
  USE(parameter6);
  TNode<Object> parameter7 = UncheckedCast<Object>(Parameter(Descriptor::kResult));
  USE(parameter7);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
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
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSReceiver> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_Callable_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2}, &label3);
    ca_.Goto(&block7);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block8);
    }
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSReceiver> tmp4;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    compiler::CodeAssemblerLabel label5(&ca_);
    tmp4 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter4}, &label5);
    ca_.Goto(&block11);
    if (label5.is_used()) {
      ca_.Bind(&label5);
      ca_.Goto(&block12);
    }
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Number> tmp6;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    compiler::CodeAssemblerLabel label7(&ca_);
    tmp6 = Cast_Number_0(state_, TNode<Object>{parameter5}, &label7);
    ca_.Goto(&block15);
    if (label7.is_used()) {
      ca_.Bind(&label7);
      ca_.Goto(&block16);
    }
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Number> tmp8;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    compiler::CodeAssemblerLabel label9(&ca_);
    tmp8 = Cast_Number_0(state_, TNode<Object>{parameter6}, &label9);
    ca_.Goto(&block19);
    if (label9.is_used()) {
      ca_.Bind(&label9);
      ca_.Goto(&block20);
    }
  }

  if (block20.is_used()) {
    ca_.Bind(&block20);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Object> tmp10;
  TNode<Number> tmp11;
  TNode<Number> tmp12;
  TNode<Object> tmp13;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp10 = CodeStubAssembler(state_).CallBuiltin(Builtins::kFastCreateDataProperty, parameter0, tmp4, tmp6, parameter7);
    tmp11 = FromConstexpr_Number_constexpr_int31_0(state_, 1);
    tmp12 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{tmp6}, TNode<Number>{tmp11});
    tmp13 = CodeStubAssembler(state_).CallBuiltin(Builtins::kArrayMapLoopContinuation, parameter0, tmp0, tmp2, parameter3, tmp4, tmp0, tmp12, tmp8);
    CodeStubAssembler(state_).Return(tmp13);
  }
}

TF_BUILTIN(ArrayMapLoopContinuation, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedCast<JSReceiver>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<JSReceiver> parameter2 = UncheckedCast<JSReceiver>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  TNode<JSReceiver> parameter4 = UncheckedCast<JSReceiver>(Parameter(Descriptor::ParameterIndex<3>()));
  USE(parameter4);
  TNode<JSReceiver> parameter5 = UncheckedCast<JSReceiver>(Parameter(Descriptor::ParameterIndex<4>()));
  USE(parameter5);
  TNode<Number> parameter6 = UncheckedCast<Number>(Parameter(Descriptor::ParameterIndex<5>()));
  USE(parameter6);
  TNode<Number> parameter7 = UncheckedCast<Number>(Parameter(Descriptor::ParameterIndex<6>()));
  USE(parameter7);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    ca_.Goto(&block3, parameter6);
  }

  TNode<Number> phi_bb3_8;
  TNode<BoolT> tmp0;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_8);
    tmp0 = NumberIsLessThan_0(state_, TNode<Number>{phi_bb3_8}, TNode<Number>{parameter7});
    ca_.Branch(tmp0, &block1, std::vector<Node*>{phi_bb3_8}, &block2, std::vector<Node*>{phi_bb3_8});
  }

  TNode<Number> phi_bb1_8;
  TNode<Oddball> tmp1;
  TNode<Oddball> tmp2;
  TNode<BoolT> tmp3;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_8);
    tmp1 = CodeStubAssembler(state_).HasProperty_Inline(TNode<Context>{parameter0}, TNode<JSReceiver>{parameter5}, TNode<Object>{phi_bb1_8});
    tmp2 = True_0(state_);
    tmp3 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp1}, TNode<HeapObject>{tmp2});
    ca_.Branch(tmp3, &block5, std::vector<Node*>{phi_bb1_8}, &block6, std::vector<Node*>{phi_bb1_8});
  }

  TNode<Number> phi_bb5_8;
  TNode<Object> tmp4;
  TNode<Object> tmp5;
  TNode<Object> tmp6;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_8);
    tmp4 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<Object>{parameter5}, TNode<Object>{phi_bb5_8});
    tmp5 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<Object>{parameter2}, TNode<Object>{parameter3}, TNode<Object>{tmp4}, TNode<Object>{phi_bb5_8}, TNode<Object>{parameter5});
    tmp6 = CodeStubAssembler(state_).CallBuiltin(Builtins::kFastCreateDataProperty, parameter0, parameter4, phi_bb5_8, tmp5);
    ca_.Goto(&block6, phi_bb5_8);
  }

  TNode<Number> phi_bb6_8;
  TNode<Number> tmp7;
  TNode<Number> tmp8;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_8);
    tmp7 = FromConstexpr_Number_constexpr_int31_0(state_, 1);
    tmp8 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{phi_bb6_8}, TNode<Number>{tmp7});
    ca_.Goto(&block3, tmp8);
  }

  TNode<Number> phi_bb2_8;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_8);
    CodeStubAssembler(state_).Return(parameter4);
  }
}

TorqueStructVector_0 NewVector_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Smi> p_length) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp1 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{p_length}, TNode<Smi>{tmp0});
    ca_.Branch(tmp1, &block2, std::vector<Node*>{}, &block3, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp2;
  TNode<FixedArray> tmp3;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp2 = CodeStubAssembler(state_).SmiUntag(TNode<Smi>{p_length});
    tmp3 = CodeStubAssembler(state_).AllocateFixedArrayWithHoles(TNode<IntPtrT>{tmp2}, CodeStubAssembler::AllocationFlag::kAllowLargeObjectAllocation);
    ca_.Goto(&block4, tmp3);
  }

  TNode<FixedArray> tmp4;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp4 = kEmptyFixedArray_0(state_);
    ca_.Goto(&block4, tmp4);
  }

  TNode<FixedArray> phi_bb4_2;
  TNode<BoolT> tmp5;
  TNode<BoolT> tmp6;
  TNode<BoolT> tmp7;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_2);
    tmp5 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    tmp6 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    tmp7 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
  return TorqueStructVector_0{TNode<FixedArray>{phi_bb4_2}, TNode<BoolT>{tmp5}, TNode<BoolT>{tmp6}, TNode<BoolT>{tmp7}};
}

TNode<JSArray> FastArrayMap_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSArray> p_fastO, TNode<Smi> p_len, TNode<JSReceiver> p_callbackfn, TNode<Object> p_thisArg, compiler::CodeAssemblerLabel* label_Bailout, compiler::TypedCodeAssemblerVariable<JSArray>* label_Bailout_parameter_0, compiler::TypedCodeAssemblerVariable<Smi>* label_Bailout_parameter_1) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, BoolT, BoolT> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, BoolT, BoolT> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, BoolT, BoolT, Smi, Smi> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, BoolT, BoolT, Smi, Smi, Smi> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, BoolT, BoolT, Smi, Smi, Smi> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, BoolT, BoolT, Smi, Smi> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, BoolT, BoolT, Smi, Smi, Smi> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, BoolT, BoolT, Smi, Smi, Smi> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, BoolT, BoolT, Smi, Smi, Object> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, BoolT, BoolT, Smi, Smi> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, BoolT, BoolT, Smi, Smi> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, BoolT, BoolT, Smi, Smi, Smi, Smi> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, BoolT, BoolT, Smi, Smi, Smi, Smi> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, BoolT, BoolT, Smi, Smi> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, BoolT, BoolT, Smi, Smi> block44(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, BoolT, Smi, Smi, Smi, Smi> block50(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, BoolT, Smi, Smi, Smi, Smi> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, Smi, Smi, Smi, Smi> block57(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, Smi, Smi, Smi, Smi> block58(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, BoolT, BoolT, Smi, Smi> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, BoolT, BoolT, Smi, Smi> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, BoolT, BoolT> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT, BoolT, BoolT> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi> block4(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi> block66(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi> block68(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi> block69(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi, Int32T> block70(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi, Int32T> block67(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi, Int32T, BoolT> block73(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi, Int32T, BoolT> block74(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi, Int32T, BoolT, BoolT> block75(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi, Int32T> block71(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi, Int32T> block72(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi> block76(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi, Smi> block81(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi, Smi> block79(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi, Smi, Smi, Smi> block87(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi, Smi, Smi, Smi> block88(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi, Smi> block93(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi, Smi> block92(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi, Smi, Smi, Smi> block98(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi, Smi, Smi, Smi> block99(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi, Smi> block90(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi, Smi> block80(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi> block77(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi, JSArray> block78(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT> block106(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT> block108(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT> block109(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Int32T> block110(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Int32T> block107(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Int32T, BoolT> block113(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Int32T, BoolT> block114(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Int32T, BoolT, BoolT> block115(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Int32T> block111(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Int32T> block112(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT> block116(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi> block121(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi> block119(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi> block127(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi> block128(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi> block133(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi> block132(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi> block138(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi, Smi, Smi> block139(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi> block130(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, Smi> block120(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT> block117(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray, BoolT, BoolT, BoolT, JSArray> block118(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSArray> block141(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<JSArray> tmp1;
  TNode<JSArray> tmp2;
  TNode<Map> tmp3;
  TNode<BoolT> tmp4;
  TNode<FixedArray> tmp5;
  TNode<BoolT> tmp6;
  TNode<BoolT> tmp7;
  TNode<BoolT> tmp8;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    std::tie(tmp1, tmp2, tmp3, tmp4) = NewFastJSArrayForReadWitness_0(state_, TNode<JSArray>{p_fastO}).Flatten();
    std::tie(tmp5, tmp6, tmp7, tmp8) = NewVector_0(state_, TNode<Context>{p_context}, TNode<Smi>{p_len}).Flatten();
    ca_.Goto(&block7, tmp0, tmp2, tmp6, tmp7, tmp8);
  }

  TNode<Smi> phi_bb7_5;
  TNode<JSArray> phi_bb7_7;
  TNode<BoolT> phi_bb7_11;
  TNode<BoolT> phi_bb7_12;
  TNode<BoolT> phi_bb7_13;
  TNode<BoolT> tmp9;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_5, &phi_bb7_7, &phi_bb7_11, &phi_bb7_12, &phi_bb7_13);
    tmp9 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb7_5}, TNode<Smi>{p_len});
    ca_.Branch(tmp9, &block5, std::vector<Node*>{phi_bb7_5, phi_bb7_7, phi_bb7_11, phi_bb7_12, phi_bb7_13}, &block6, std::vector<Node*>{phi_bb7_5, phi_bb7_7, phi_bb7_11, phi_bb7_12, phi_bb7_13});
  }

  TNode<Smi> phi_bb5_5;
  TNode<JSArray> phi_bb5_7;
  TNode<BoolT> phi_bb5_11;
  TNode<BoolT> phi_bb5_12;
  TNode<BoolT> phi_bb5_13;
  TNode<IntPtrT> tmp10;
  TNode<Map> tmp11;
  TNode<BoolT> tmp12;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_5, &phi_bb5_7, &phi_bb5_11, &phi_bb5_12, &phi_bb5_13);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp11 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp1, tmp10});
    tmp12 = CodeStubAssembler(state_).TaggedNotEqual(TNode<HeapObject>{tmp11}, TNode<HeapObject>{tmp3});
    ca_.Branch(tmp12, &block12, std::vector<Node*>{phi_bb5_5, phi_bb5_7, phi_bb5_11, phi_bb5_12, phi_bb5_13}, &block13, std::vector<Node*>{phi_bb5_5, phi_bb5_7, phi_bb5_11, phi_bb5_12, phi_bb5_13});
  }

  TNode<Smi> phi_bb12_5;
  TNode<JSArray> phi_bb12_7;
  TNode<BoolT> phi_bb12_11;
  TNode<BoolT> phi_bb12_12;
  TNode<BoolT> phi_bb12_13;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_5, &phi_bb12_7, &phi_bb12_11, &phi_bb12_12, &phi_bb12_13);
    ca_.Goto(&block10, phi_bb12_5, phi_bb12_7, phi_bb12_11, phi_bb12_12, phi_bb12_13);
  }

  TNode<Smi> phi_bb13_5;
  TNode<JSArray> phi_bb13_7;
  TNode<BoolT> phi_bb13_11;
  TNode<BoolT> phi_bb13_12;
  TNode<BoolT> phi_bb13_13;
  TNode<BoolT> tmp13;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_5, &phi_bb13_7, &phi_bb13_11, &phi_bb13_12, &phi_bb13_13);
    tmp13 = CodeStubAssembler(state_).IsNoElementsProtectorCellInvalid();
    ca_.Branch(tmp13, &block14, std::vector<Node*>{phi_bb13_5, phi_bb13_7, phi_bb13_11, phi_bb13_12, phi_bb13_13}, &block15, std::vector<Node*>{phi_bb13_5, phi_bb13_7, phi_bb13_11, phi_bb13_12, phi_bb13_13});
  }

  TNode<Smi> phi_bb14_5;
  TNode<JSArray> phi_bb14_7;
  TNode<BoolT> phi_bb14_11;
  TNode<BoolT> phi_bb14_12;
  TNode<BoolT> phi_bb14_13;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_5, &phi_bb14_7, &phi_bb14_11, &phi_bb14_12, &phi_bb14_13);
    ca_.Goto(&block10, phi_bb14_5, phi_bb14_7, phi_bb14_11, phi_bb14_12, phi_bb14_13);
  }

  TNode<Smi> phi_bb15_5;
  TNode<JSArray> phi_bb15_7;
  TNode<BoolT> phi_bb15_11;
  TNode<BoolT> phi_bb15_12;
  TNode<BoolT> phi_bb15_13;
  TNode<JSArray> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<Number> tmp16;
  TNode<BoolT> tmp17;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_5, &phi_bb15_7, &phi_bb15_11, &phi_bb15_12, &phi_bb15_13);
    tmp14 = (TNode<JSArray>{tmp1});
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp16 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{tmp14, tmp15});
    tmp17 = NumberIsGreaterThanOrEqual_0(state_, TNode<Number>{phi_bb15_5}, TNode<Number>{tmp16});
    ca_.Branch(tmp17, &block16, std::vector<Node*>{phi_bb15_5, phi_bb15_11, phi_bb15_12, phi_bb15_13}, &block17, std::vector<Node*>{phi_bb15_5, phi_bb15_11, phi_bb15_12, phi_bb15_13});
  }

  TNode<Smi> phi_bb10_5;
  TNode<JSArray> phi_bb10_7;
  TNode<BoolT> phi_bb10_11;
  TNode<BoolT> phi_bb10_12;
  TNode<BoolT> phi_bb10_13;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_5, &phi_bb10_7, &phi_bb10_11, &phi_bb10_12, &phi_bb10_13);
    ca_.Goto(&block4, phi_bb10_5, phi_bb10_7, phi_bb10_11, phi_bb10_12, phi_bb10_13, phi_bb10_5);
  }

  TNode<Smi> phi_bb16_5;
  TNode<BoolT> phi_bb16_11;
  TNode<BoolT> phi_bb16_12;
  TNode<BoolT> phi_bb16_13;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_5, &phi_bb16_11, &phi_bb16_12, &phi_bb16_13);
    ca_.Goto(&block4, phi_bb16_5, tmp14, phi_bb16_11, phi_bb16_12, phi_bb16_13, phi_bb16_5);
  }

  TNode<Smi> phi_bb17_5;
  TNode<BoolT> phi_bb17_11;
  TNode<BoolT> phi_bb17_12;
  TNode<BoolT> phi_bb17_13;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_5, &phi_bb17_11, &phi_bb17_12, &phi_bb17_13);
    ca_.Branch(tmp4, &block22, std::vector<Node*>{phi_bb17_5, phi_bb17_11, phi_bb17_12, phi_bb17_13, phi_bb17_5, phi_bb17_5}, &block23, std::vector<Node*>{phi_bb17_5, phi_bb17_11, phi_bb17_12, phi_bb17_13, phi_bb17_5, phi_bb17_5});
  }

  TNode<Smi> phi_bb22_5;
  TNode<BoolT> phi_bb22_11;
  TNode<BoolT> phi_bb22_12;
  TNode<BoolT> phi_bb22_13;
  TNode<Smi> phi_bb22_14;
  TNode<Smi> phi_bb22_17;
  TNode<Object> tmp18;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_5, &phi_bb22_11, &phi_bb22_12, &phi_bb22_13, &phi_bb22_14, &phi_bb22_17);
    compiler::CodeAssemblerLabel label19(&ca_);
    tmp18 = LoadElementNoHole_FixedDoubleArray_0(state_, TNode<Context>{p_context}, TNode<JSArray>{tmp14}, TNode<Smi>{phi_bb22_17}, &label19);
    ca_.Goto(&block25, phi_bb22_5, phi_bb22_11, phi_bb22_12, phi_bb22_13, phi_bb22_14, phi_bb22_17, phi_bb22_17);
    if (label19.is_used()) {
      ca_.Bind(&label19);
      ca_.Goto(&block26, phi_bb22_5, phi_bb22_11, phi_bb22_12, phi_bb22_13, phi_bb22_14, phi_bb22_17, phi_bb22_17);
    }
  }

  TNode<Smi> phi_bb26_5;
  TNode<BoolT> phi_bb26_11;
  TNode<BoolT> phi_bb26_12;
  TNode<BoolT> phi_bb26_13;
  TNode<Smi> phi_bb26_14;
  TNode<Smi> phi_bb26_17;
  TNode<Smi> phi_bb26_19;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_5, &phi_bb26_11, &phi_bb26_12, &phi_bb26_13, &phi_bb26_14, &phi_bb26_17, &phi_bb26_19);
    ca_.Goto(&block20, phi_bb26_5, phi_bb26_11, phi_bb26_12, phi_bb26_13);
  }

  TNode<Smi> phi_bb25_5;
  TNode<BoolT> phi_bb25_11;
  TNode<BoolT> phi_bb25_12;
  TNode<BoolT> phi_bb25_13;
  TNode<Smi> phi_bb25_14;
  TNode<Smi> phi_bb25_17;
  TNode<Smi> phi_bb25_19;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_5, &phi_bb25_11, &phi_bb25_12, &phi_bb25_13, &phi_bb25_14, &phi_bb25_17, &phi_bb25_19);
    ca_.Goto(&block21, phi_bb25_5, phi_bb25_11, phi_bb25_12, phi_bb25_13, phi_bb25_14, phi_bb25_17, tmp18);
  }

  TNode<Smi> phi_bb23_5;
  TNode<BoolT> phi_bb23_11;
  TNode<BoolT> phi_bb23_12;
  TNode<BoolT> phi_bb23_13;
  TNode<Smi> phi_bb23_14;
  TNode<Smi> phi_bb23_17;
  TNode<Object> tmp20;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_5, &phi_bb23_11, &phi_bb23_12, &phi_bb23_13, &phi_bb23_14, &phi_bb23_17);
    compiler::CodeAssemblerLabel label21(&ca_);
    tmp20 = LoadElementNoHole_FixedArray_0(state_, TNode<Context>{p_context}, TNode<JSArray>{tmp14}, TNode<Smi>{phi_bb23_17}, &label21);
    ca_.Goto(&block27, phi_bb23_5, phi_bb23_11, phi_bb23_12, phi_bb23_13, phi_bb23_14, phi_bb23_17, phi_bb23_17);
    if (label21.is_used()) {
      ca_.Bind(&label21);
      ca_.Goto(&block28, phi_bb23_5, phi_bb23_11, phi_bb23_12, phi_bb23_13, phi_bb23_14, phi_bb23_17, phi_bb23_17);
    }
  }

  TNode<Smi> phi_bb28_5;
  TNode<BoolT> phi_bb28_11;
  TNode<BoolT> phi_bb28_12;
  TNode<BoolT> phi_bb28_13;
  TNode<Smi> phi_bb28_14;
  TNode<Smi> phi_bb28_17;
  TNode<Smi> phi_bb28_19;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_5, &phi_bb28_11, &phi_bb28_12, &phi_bb28_13, &phi_bb28_14, &phi_bb28_17, &phi_bb28_19);
    ca_.Goto(&block20, phi_bb28_5, phi_bb28_11, phi_bb28_12, phi_bb28_13);
  }

  TNode<Smi> phi_bb27_5;
  TNode<BoolT> phi_bb27_11;
  TNode<BoolT> phi_bb27_12;
  TNode<BoolT> phi_bb27_13;
  TNode<Smi> phi_bb27_14;
  TNode<Smi> phi_bb27_17;
  TNode<Smi> phi_bb27_19;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_5, &phi_bb27_11, &phi_bb27_12, &phi_bb27_13, &phi_bb27_14, &phi_bb27_17, &phi_bb27_19);
    ca_.Goto(&block21, phi_bb27_5, phi_bb27_11, phi_bb27_12, phi_bb27_13, phi_bb27_14, phi_bb27_17, tmp20);
  }

  TNode<Smi> phi_bb21_5;
  TNode<BoolT> phi_bb21_11;
  TNode<BoolT> phi_bb21_12;
  TNode<BoolT> phi_bb21_13;
  TNode<Smi> phi_bb21_14;
  TNode<Smi> phi_bb21_17;
  TNode<Object> phi_bb21_18;
  TNode<Object> tmp22;
  TNode<Smi> tmp23;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_5, &phi_bb21_11, &phi_bb21_12, &phi_bb21_13, &phi_bb21_14, &phi_bb21_17, &phi_bb21_18);
    tmp22 = CodeStubAssembler(state_).Call(TNode<Context>{p_context}, TNode<Object>{p_callbackfn}, TNode<Object>{p_thisArg}, TNode<Object>{phi_bb21_18}, TNode<Object>{phi_bb21_5}, TNode<Object>{tmp14});
    compiler::CodeAssemblerLabel label24(&ca_);
    tmp23 = Cast_Smi_0(state_, TNode<Object>{tmp22}, &label24);
    ca_.Goto(&block33, phi_bb21_5, phi_bb21_11, phi_bb21_12, phi_bb21_13, phi_bb21_5, phi_bb21_5);
    if (label24.is_used()) {
      ca_.Bind(&label24);
      ca_.Goto(&block34, phi_bb21_5, phi_bb21_11, phi_bb21_12, phi_bb21_13, phi_bb21_5, phi_bb21_5);
    }
  }

  TNode<Smi> phi_bb34_5;
  TNode<BoolT> phi_bb34_11;
  TNode<BoolT> phi_bb34_12;
  TNode<BoolT> phi_bb34_13;
  TNode<Smi> phi_bb34_16;
  TNode<Smi> phi_bb34_20;
  TNode<HeapNumber> tmp25;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_5, &phi_bb34_11, &phi_bb34_12, &phi_bb34_13, &phi_bb34_16, &phi_bb34_20);
    compiler::CodeAssemblerLabel label26(&ca_);
    tmp25 = Cast_HeapNumber_0(state_, TNode<HeapObject>{ca_.UncheckedCast<HeapObject>(tmp22)}, &label26);
    ca_.Goto(&block44, phi_bb34_5, phi_bb34_11, phi_bb34_12, phi_bb34_13, phi_bb34_16, phi_bb34_20);
    if (label26.is_used()) {
      ca_.Bind(&label26);
      ca_.Goto(&block45, phi_bb34_5, phi_bb34_11, phi_bb34_12, phi_bb34_13, phi_bb34_16, phi_bb34_20);
    }
  }

  TNode<Smi> phi_bb33_5;
  TNode<BoolT> phi_bb33_11;
  TNode<BoolT> phi_bb33_12;
  TNode<BoolT> phi_bb33_13;
  TNode<Smi> phi_bb33_16;
  TNode<Smi> phi_bb33_20;
  TNode<IntPtrT> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<Smi> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<IntPtrT> tmp32;
  TNode<UintPtrT> tmp33;
  TNode<UintPtrT> tmp34;
  TNode<BoolT> tmp35;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_5, &phi_bb33_11, &phi_bb33_12, &phi_bb33_13, &phi_bb33_16, &phi_bb33_20);
    tmp27 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp28 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp29 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp30 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp5, tmp29});
    tmp31 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp30});
    tmp32 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb33_20});
    tmp33 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp32});
    tmp34 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp31});
    tmp35 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp33}, TNode<UintPtrT>{tmp34});
    ca_.Branch(tmp35, &block39, std::vector<Node*>{phi_bb33_5, phi_bb33_11, phi_bb33_12, phi_bb33_13, phi_bb33_16, phi_bb33_20, phi_bb33_20, phi_bb33_20}, &block40, std::vector<Node*>{phi_bb33_5, phi_bb33_11, phi_bb33_12, phi_bb33_13, phi_bb33_16, phi_bb33_20, phi_bb33_20, phi_bb33_20});
  }

  TNode<Smi> phi_bb39_5;
  TNode<BoolT> phi_bb39_11;
  TNode<BoolT> phi_bb39_12;
  TNode<BoolT> phi_bb39_13;
  TNode<Smi> phi_bb39_16;
  TNode<Smi> phi_bb39_20;
  TNode<Smi> phi_bb39_28;
  TNode<Smi> phi_bb39_29;
  TNode<IntPtrT> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<IntPtrT> tmp38;
  TNode<HeapObject> tmp39;
  TNode<IntPtrT> tmp40;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_5, &phi_bb39_11, &phi_bb39_12, &phi_bb39_13, &phi_bb39_16, &phi_bb39_20, &phi_bb39_28, &phi_bb39_29);
    tmp36 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp37 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp32}, TNode<IntPtrT>{tmp36});
    tmp38 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp27}, TNode<IntPtrT>{tmp37});
    std::tie(tmp39, tmp40) = NewReference_Object_0(state_, TNode<HeapObject>{tmp5}, TNode<IntPtrT>{tmp38}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp39, tmp40}, tmp23);
    ca_.Goto(&block31, phi_bb39_5, phi_bb39_11, phi_bb39_12, phi_bb39_13, phi_bb39_16, phi_bb39_20);
  }

  TNode<Smi> phi_bb40_5;
  TNode<BoolT> phi_bb40_11;
  TNode<BoolT> phi_bb40_12;
  TNode<BoolT> phi_bb40_13;
  TNode<Smi> phi_bb40_16;
  TNode<Smi> phi_bb40_20;
  TNode<Smi> phi_bb40_28;
  TNode<Smi> phi_bb40_29;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_5, &phi_bb40_11, &phi_bb40_12, &phi_bb40_13, &phi_bb40_16, &phi_bb40_20, &phi_bb40_28, &phi_bb40_29);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb45_5;
  TNode<BoolT> phi_bb45_11;
  TNode<BoolT> phi_bb45_12;
  TNode<BoolT> phi_bb45_13;
  TNode<Smi> phi_bb45_16;
  TNode<Smi> phi_bb45_20;
  TNode<BoolT> tmp41;
  TNode<BoolT> tmp42;
  TNode<IntPtrT> tmp43;
  TNode<IntPtrT> tmp44;
  TNode<IntPtrT> tmp45;
  TNode<Smi> tmp46;
  TNode<IntPtrT> tmp47;
  TNode<IntPtrT> tmp48;
  TNode<UintPtrT> tmp49;
  TNode<UintPtrT> tmp50;
  TNode<BoolT> tmp51;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_5, &phi_bb45_11, &phi_bb45_12, &phi_bb45_13, &phi_bb45_16, &phi_bb45_20);
    tmp41 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp42 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp43 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp44 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp45 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp46 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp5, tmp45});
    tmp47 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp46});
    tmp48 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb45_20});
    tmp49 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp48});
    tmp50 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp47});
    tmp51 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp49}, TNode<UintPtrT>{tmp50});
    ca_.Branch(tmp51, &block57, std::vector<Node*>{phi_bb45_5, phi_bb45_13, phi_bb45_16, phi_bb45_20, phi_bb45_20, phi_bb45_20}, &block58, std::vector<Node*>{phi_bb45_5, phi_bb45_13, phi_bb45_16, phi_bb45_20, phi_bb45_20, phi_bb45_20});
  }

  TNode<Smi> phi_bb44_5;
  TNode<BoolT> phi_bb44_11;
  TNode<BoolT> phi_bb44_12;
  TNode<BoolT> phi_bb44_13;
  TNode<Smi> phi_bb44_16;
  TNode<Smi> phi_bb44_20;
  TNode<BoolT> tmp52;
  TNode<IntPtrT> tmp53;
  TNode<IntPtrT> tmp54;
  TNode<IntPtrT> tmp55;
  TNode<Smi> tmp56;
  TNode<IntPtrT> tmp57;
  TNode<IntPtrT> tmp58;
  TNode<UintPtrT> tmp59;
  TNode<UintPtrT> tmp60;
  TNode<BoolT> tmp61;
  if (block44.is_used()) {
    ca_.Bind(&block44, &phi_bb44_5, &phi_bb44_11, &phi_bb44_12, &phi_bb44_13, &phi_bb44_16, &phi_bb44_20);
    tmp52 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp53 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp54 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp55 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp56 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp5, tmp55});
    tmp57 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp56});
    tmp58 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb44_20});
    tmp59 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp58});
    tmp60 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp57});
    tmp61 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp59}, TNode<UintPtrT>{tmp60});
    ca_.Branch(tmp61, &block50, std::vector<Node*>{phi_bb44_5, phi_bb44_12, phi_bb44_13, phi_bb44_16, phi_bb44_20, phi_bb44_20, phi_bb44_20}, &block51, std::vector<Node*>{phi_bb44_5, phi_bb44_12, phi_bb44_13, phi_bb44_16, phi_bb44_20, phi_bb44_20, phi_bb44_20});
  }

  TNode<Smi> phi_bb50_5;
  TNode<BoolT> phi_bb50_12;
  TNode<BoolT> phi_bb50_13;
  TNode<Smi> phi_bb50_16;
  TNode<Smi> phi_bb50_20;
  TNode<Smi> phi_bb50_28;
  TNode<Smi> phi_bb50_29;
  TNode<IntPtrT> tmp62;
  TNode<IntPtrT> tmp63;
  TNode<IntPtrT> tmp64;
  TNode<HeapObject> tmp65;
  TNode<IntPtrT> tmp66;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_5, &phi_bb50_12, &phi_bb50_13, &phi_bb50_16, &phi_bb50_20, &phi_bb50_28, &phi_bb50_29);
    tmp62 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp63 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp58}, TNode<IntPtrT>{tmp62});
    tmp64 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp53}, TNode<IntPtrT>{tmp63});
    std::tie(tmp65, tmp66) = NewReference_Object_0(state_, TNode<HeapObject>{tmp5}, TNode<IntPtrT>{tmp64}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp65, tmp66}, tmp25);
    ca_.Goto(&block42, phi_bb50_5, tmp52, phi_bb50_12, phi_bb50_13, phi_bb50_16, phi_bb50_20);
  }

  TNode<Smi> phi_bb51_5;
  TNode<BoolT> phi_bb51_12;
  TNode<BoolT> phi_bb51_13;
  TNode<Smi> phi_bb51_16;
  TNode<Smi> phi_bb51_20;
  TNode<Smi> phi_bb51_28;
  TNode<Smi> phi_bb51_29;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_5, &phi_bb51_12, &phi_bb51_13, &phi_bb51_16, &phi_bb51_20, &phi_bb51_28, &phi_bb51_29);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb57_5;
  TNode<BoolT> phi_bb57_13;
  TNode<Smi> phi_bb57_16;
  TNode<Smi> phi_bb57_20;
  TNode<Smi> phi_bb57_28;
  TNode<Smi> phi_bb57_29;
  TNode<IntPtrT> tmp67;
  TNode<IntPtrT> tmp68;
  TNode<IntPtrT> tmp69;
  TNode<HeapObject> tmp70;
  TNode<IntPtrT> tmp71;
  if (block57.is_used()) {
    ca_.Bind(&block57, &phi_bb57_5, &phi_bb57_13, &phi_bb57_16, &phi_bb57_20, &phi_bb57_28, &phi_bb57_29);
    tmp67 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp68 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp48}, TNode<IntPtrT>{tmp67});
    tmp69 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp43}, TNode<IntPtrT>{tmp68});
    std::tie(tmp70, tmp71) = NewReference_Object_0(state_, TNode<HeapObject>{tmp5}, TNode<IntPtrT>{tmp69}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp70, tmp71}, ca_.UncheckedCast<HeapObject>(tmp22));
    ca_.Goto(&block42, phi_bb57_5, tmp41, tmp42, phi_bb57_13, phi_bb57_16, phi_bb57_20);
  }

  TNode<Smi> phi_bb58_5;
  TNode<BoolT> phi_bb58_13;
  TNode<Smi> phi_bb58_16;
  TNode<Smi> phi_bb58_20;
  TNode<Smi> phi_bb58_28;
  TNode<Smi> phi_bb58_29;
  if (block58.is_used()) {
    ca_.Bind(&block58, &phi_bb58_5, &phi_bb58_13, &phi_bb58_16, &phi_bb58_20, &phi_bb58_28, &phi_bb58_29);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb42_5;
  TNode<BoolT> phi_bb42_11;
  TNode<BoolT> phi_bb42_12;
  TNode<BoolT> phi_bb42_13;
  TNode<Smi> phi_bb42_16;
  TNode<Smi> phi_bb42_20;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_5, &phi_bb42_11, &phi_bb42_12, &phi_bb42_13, &phi_bb42_16, &phi_bb42_20);
    ca_.Goto(&block31, phi_bb42_5, phi_bb42_11, phi_bb42_12, phi_bb42_13, phi_bb42_16, phi_bb42_20);
  }

  TNode<Smi> phi_bb31_5;
  TNode<BoolT> phi_bb31_11;
  TNode<BoolT> phi_bb31_12;
  TNode<BoolT> phi_bb31_13;
  TNode<Smi> phi_bb31_16;
  TNode<Smi> phi_bb31_20;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_5, &phi_bb31_11, &phi_bb31_12, &phi_bb31_13, &phi_bb31_16, &phi_bb31_20);
    ca_.Goto(&block19, phi_bb31_5, phi_bb31_11, phi_bb31_12, phi_bb31_13);
  }

  TNode<Smi> phi_bb20_5;
  TNode<BoolT> phi_bb20_11;
  TNode<BoolT> phi_bb20_12;
  TNode<BoolT> phi_bb20_13;
  TNode<BoolT> tmp72;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_5, &phi_bb20_11, &phi_bb20_12, &phi_bb20_13);
    tmp72 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block19, phi_bb20_5, phi_bb20_11, phi_bb20_12, tmp72);
  }

  TNode<Smi> phi_bb19_5;
  TNode<BoolT> phi_bb19_11;
  TNode<BoolT> phi_bb19_12;
  TNode<BoolT> phi_bb19_13;
  TNode<Smi> tmp73;
  TNode<Smi> tmp74;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_5, &phi_bb19_11, &phi_bb19_12, &phi_bb19_13);
    tmp73 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp74 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb19_5}, TNode<Smi>{tmp73});
    ca_.Goto(&block7, tmp74, tmp14, phi_bb19_11, phi_bb19_12, phi_bb19_13);
  }

  TNode<Smi> phi_bb6_5;
  TNode<JSArray> phi_bb6_7;
  TNode<BoolT> phi_bb6_11;
  TNode<BoolT> phi_bb6_12;
  TNode<BoolT> phi_bb6_13;
  TNode<IntPtrT> tmp75;
  TNode<Smi> tmp76;
  TNode<Int32T> tmp77;
  TNode<BoolT> tmp78;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_5, &phi_bb6_7, &phi_bb6_11, &phi_bb6_12, &phi_bb6_13);
    tmp75 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp76 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp5, tmp75});
    tmp77 = FromConstexpr_ElementsKind_constexpr_PACKED_SMI_ELEMENTS_0(state_, ElementsKind::PACKED_SMI_ELEMENTS);
    tmp78 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{phi_bb6_11});
    ca_.Branch(tmp78, &block106, std::vector<Node*>{phi_bb6_5, phi_bb6_7, phi_bb6_11, phi_bb6_12, phi_bb6_13}, &block107, std::vector<Node*>{phi_bb6_5, phi_bb6_7, phi_bb6_11, phi_bb6_12, phi_bb6_13, tmp77});
  }

  TNode<Smi> phi_bb4_5;
  TNode<JSArray> phi_bb4_7;
  TNode<BoolT> phi_bb4_11;
  TNode<BoolT> phi_bb4_12;
  TNode<BoolT> phi_bb4_13;
  TNode<Smi> phi_bb4_14;
  TNode<IntPtrT> tmp79;
  TNode<Smi> tmp80;
  TNode<Int32T> tmp81;
  TNode<BoolT> tmp82;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_5, &phi_bb4_7, &phi_bb4_11, &phi_bb4_12, &phi_bb4_13, &phi_bb4_14);
    tmp79 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp80 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp5, tmp79});
    tmp81 = FromConstexpr_ElementsKind_constexpr_PACKED_SMI_ELEMENTS_0(state_, ElementsKind::PACKED_SMI_ELEMENTS);
    tmp82 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{phi_bb4_11});
    ca_.Branch(tmp82, &block66, std::vector<Node*>{phi_bb4_5, phi_bb4_7, phi_bb4_11, phi_bb4_12, phi_bb4_13, phi_bb4_14, phi_bb4_14, phi_bb4_14}, &block67, std::vector<Node*>{phi_bb4_5, phi_bb4_7, phi_bb4_11, phi_bb4_12, phi_bb4_13, phi_bb4_14, phi_bb4_14, phi_bb4_14, tmp81});
  }

  TNode<Smi> phi_bb66_5;
  TNode<JSArray> phi_bb66_7;
  TNode<BoolT> phi_bb66_11;
  TNode<BoolT> phi_bb66_12;
  TNode<BoolT> phi_bb66_13;
  TNode<Smi> phi_bb66_14;
  TNode<Smi> phi_bb66_15;
  TNode<Smi> phi_bb66_18;
  if (block66.is_used()) {
    ca_.Bind(&block66, &phi_bb66_5, &phi_bb66_7, &phi_bb66_11, &phi_bb66_12, &phi_bb66_13, &phi_bb66_14, &phi_bb66_15, &phi_bb66_18);
    ca_.Branch(phi_bb66_12, &block68, std::vector<Node*>{phi_bb66_5, phi_bb66_7, phi_bb66_11, phi_bb66_12, phi_bb66_13, phi_bb66_14, phi_bb66_15, phi_bb66_18}, &block69, std::vector<Node*>{phi_bb66_5, phi_bb66_7, phi_bb66_11, phi_bb66_12, phi_bb66_13, phi_bb66_14, phi_bb66_15, phi_bb66_18});
  }

  TNode<Smi> phi_bb68_5;
  TNode<JSArray> phi_bb68_7;
  TNode<BoolT> phi_bb68_11;
  TNode<BoolT> phi_bb68_12;
  TNode<BoolT> phi_bb68_13;
  TNode<Smi> phi_bb68_14;
  TNode<Smi> phi_bb68_15;
  TNode<Smi> phi_bb68_18;
  TNode<Int32T> tmp83;
  if (block68.is_used()) {
    ca_.Bind(&block68, &phi_bb68_5, &phi_bb68_7, &phi_bb68_11, &phi_bb68_12, &phi_bb68_13, &phi_bb68_14, &phi_bb68_15, &phi_bb68_18);
    tmp83 = FromConstexpr_ElementsKind_constexpr_PACKED_DOUBLE_ELEMENTS_0(state_, ElementsKind::PACKED_DOUBLE_ELEMENTS);
    ca_.Goto(&block70, phi_bb68_5, phi_bb68_7, phi_bb68_11, phi_bb68_12, phi_bb68_13, phi_bb68_14, phi_bb68_15, phi_bb68_18, tmp83);
  }

  TNode<Smi> phi_bb69_5;
  TNode<JSArray> phi_bb69_7;
  TNode<BoolT> phi_bb69_11;
  TNode<BoolT> phi_bb69_12;
  TNode<BoolT> phi_bb69_13;
  TNode<Smi> phi_bb69_14;
  TNode<Smi> phi_bb69_15;
  TNode<Smi> phi_bb69_18;
  TNode<Int32T> tmp84;
  if (block69.is_used()) {
    ca_.Bind(&block69, &phi_bb69_5, &phi_bb69_7, &phi_bb69_11, &phi_bb69_12, &phi_bb69_13, &phi_bb69_14, &phi_bb69_15, &phi_bb69_18);
    tmp84 = FromConstexpr_ElementsKind_constexpr_PACKED_ELEMENTS_0(state_, ElementsKind::PACKED_ELEMENTS);
    ca_.Goto(&block70, phi_bb69_5, phi_bb69_7, phi_bb69_11, phi_bb69_12, phi_bb69_13, phi_bb69_14, phi_bb69_15, phi_bb69_18, tmp84);
  }

  TNode<Smi> phi_bb70_5;
  TNode<JSArray> phi_bb70_7;
  TNode<BoolT> phi_bb70_11;
  TNode<BoolT> phi_bb70_12;
  TNode<BoolT> phi_bb70_13;
  TNode<Smi> phi_bb70_14;
  TNode<Smi> phi_bb70_15;
  TNode<Smi> phi_bb70_18;
  TNode<Int32T> phi_bb70_20;
  if (block70.is_used()) {
    ca_.Bind(&block70, &phi_bb70_5, &phi_bb70_7, &phi_bb70_11, &phi_bb70_12, &phi_bb70_13, &phi_bb70_14, &phi_bb70_15, &phi_bb70_18, &phi_bb70_20);
    ca_.Goto(&block67, phi_bb70_5, phi_bb70_7, phi_bb70_11, phi_bb70_12, phi_bb70_13, phi_bb70_14, phi_bb70_15, phi_bb70_18, phi_bb70_20);
  }

  TNode<Smi> phi_bb67_5;
  TNode<JSArray> phi_bb67_7;
  TNode<BoolT> phi_bb67_11;
  TNode<BoolT> phi_bb67_12;
  TNode<BoolT> phi_bb67_13;
  TNode<Smi> phi_bb67_14;
  TNode<Smi> phi_bb67_15;
  TNode<Smi> phi_bb67_18;
  TNode<Int32T> phi_bb67_20;
  if (block67.is_used()) {
    ca_.Bind(&block67, &phi_bb67_5, &phi_bb67_7, &phi_bb67_11, &phi_bb67_12, &phi_bb67_13, &phi_bb67_14, &phi_bb67_15, &phi_bb67_18, &phi_bb67_20);
    ca_.Branch(phi_bb67_13, &block73, std::vector<Node*>{phi_bb67_5, phi_bb67_7, phi_bb67_11, phi_bb67_12, phi_bb67_13, phi_bb67_14, phi_bb67_15, phi_bb67_18, phi_bb67_20, phi_bb67_13}, &block74, std::vector<Node*>{phi_bb67_5, phi_bb67_7, phi_bb67_11, phi_bb67_12, phi_bb67_13, phi_bb67_14, phi_bb67_15, phi_bb67_18, phi_bb67_20, phi_bb67_13});
  }

  TNode<Smi> phi_bb73_5;
  TNode<JSArray> phi_bb73_7;
  TNode<BoolT> phi_bb73_11;
  TNode<BoolT> phi_bb73_12;
  TNode<BoolT> phi_bb73_13;
  TNode<Smi> phi_bb73_14;
  TNode<Smi> phi_bb73_15;
  TNode<Smi> phi_bb73_18;
  TNode<Int32T> phi_bb73_20;
  TNode<BoolT> phi_bb73_21;
  TNode<BoolT> tmp85;
  if (block73.is_used()) {
    ca_.Bind(&block73, &phi_bb73_5, &phi_bb73_7, &phi_bb73_11, &phi_bb73_12, &phi_bb73_13, &phi_bb73_14, &phi_bb73_15, &phi_bb73_18, &phi_bb73_20, &phi_bb73_21);
    tmp85 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block75, phi_bb73_5, phi_bb73_7, phi_bb73_11, phi_bb73_12, phi_bb73_13, phi_bb73_14, phi_bb73_15, phi_bb73_18, phi_bb73_20, phi_bb73_21, tmp85);
  }

  TNode<Smi> phi_bb74_5;
  TNode<JSArray> phi_bb74_7;
  TNode<BoolT> phi_bb74_11;
  TNode<BoolT> phi_bb74_12;
  TNode<BoolT> phi_bb74_13;
  TNode<Smi> phi_bb74_14;
  TNode<Smi> phi_bb74_15;
  TNode<Smi> phi_bb74_18;
  TNode<Int32T> phi_bb74_20;
  TNode<BoolT> phi_bb74_21;
  TNode<BoolT> tmp86;
  if (block74.is_used()) {
    ca_.Bind(&block74, &phi_bb74_5, &phi_bb74_7, &phi_bb74_11, &phi_bb74_12, &phi_bb74_13, &phi_bb74_14, &phi_bb74_15, &phi_bb74_18, &phi_bb74_20, &phi_bb74_21);
    tmp86 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb74_18}, TNode<Smi>{tmp80});
    ca_.Goto(&block75, phi_bb74_5, phi_bb74_7, phi_bb74_11, phi_bb74_12, phi_bb74_13, phi_bb74_14, phi_bb74_15, phi_bb74_18, phi_bb74_20, phi_bb74_21, tmp86);
  }

  TNode<Smi> phi_bb75_5;
  TNode<JSArray> phi_bb75_7;
  TNode<BoolT> phi_bb75_11;
  TNode<BoolT> phi_bb75_12;
  TNode<BoolT> phi_bb75_13;
  TNode<Smi> phi_bb75_14;
  TNode<Smi> phi_bb75_15;
  TNode<Smi> phi_bb75_18;
  TNode<Int32T> phi_bb75_20;
  TNode<BoolT> phi_bb75_21;
  TNode<BoolT> phi_bb75_22;
  if (block75.is_used()) {
    ca_.Bind(&block75, &phi_bb75_5, &phi_bb75_7, &phi_bb75_11, &phi_bb75_12, &phi_bb75_13, &phi_bb75_14, &phi_bb75_15, &phi_bb75_18, &phi_bb75_20, &phi_bb75_21, &phi_bb75_22);
    ca_.Branch(phi_bb75_22, &block71, std::vector<Node*>{phi_bb75_5, phi_bb75_7, phi_bb75_11, phi_bb75_12, phi_bb75_13, phi_bb75_14, phi_bb75_15, phi_bb75_18, phi_bb75_20}, &block72, std::vector<Node*>{phi_bb75_5, phi_bb75_7, phi_bb75_11, phi_bb75_12, phi_bb75_13, phi_bb75_14, phi_bb75_15, phi_bb75_18, phi_bb75_20});
  }

  TNode<Smi> phi_bb71_5;
  TNode<JSArray> phi_bb71_7;
  TNode<BoolT> phi_bb71_11;
  TNode<BoolT> phi_bb71_12;
  TNode<BoolT> phi_bb71_13;
  TNode<Smi> phi_bb71_14;
  TNode<Smi> phi_bb71_15;
  TNode<Smi> phi_bb71_18;
  TNode<Int32T> phi_bb71_20;
  TNode<Int32T> tmp87;
  if (block71.is_used()) {
    ca_.Bind(&block71, &phi_bb71_5, &phi_bb71_7, &phi_bb71_11, &phi_bb71_12, &phi_bb71_13, &phi_bb71_14, &phi_bb71_15, &phi_bb71_18, &phi_bb71_20);
    tmp87 = FastHoleyElementsKind_0(state_, TNode<Int32T>{phi_bb71_20});
    ca_.Goto(&block72, phi_bb71_5, phi_bb71_7, phi_bb71_11, phi_bb71_12, phi_bb71_13, phi_bb71_14, phi_bb71_15, phi_bb71_18, tmp87);
  }

  TNode<Smi> phi_bb72_5;
  TNode<JSArray> phi_bb72_7;
  TNode<BoolT> phi_bb72_11;
  TNode<BoolT> phi_bb72_12;
  TNode<BoolT> phi_bb72_13;
  TNode<Smi> phi_bb72_14;
  TNode<Smi> phi_bb72_15;
  TNode<Smi> phi_bb72_18;
  TNode<Int32T> phi_bb72_20;
  TNode<NativeContext> tmp88;
  TNode<Map> tmp89;
  TNode<BoolT> tmp90;
  if (block72.is_used()) {
    ca_.Bind(&block72, &phi_bb72_5, &phi_bb72_7, &phi_bb72_11, &phi_bb72_12, &phi_bb72_13, &phi_bb72_14, &phi_bb72_15, &phi_bb72_18, &phi_bb72_20);
    tmp88 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{p_context});
    tmp89 = CodeStubAssembler(state_).LoadJSArrayElementsMap(TNode<Int32T>{phi_bb72_20}, TNode<NativeContext>{tmp88});
    tmp90 = CodeStubAssembler(state_).IsDoubleElementsKind(TNode<Int32T>{phi_bb72_20});
    ca_.Branch(tmp90, &block76, std::vector<Node*>{phi_bb72_5, phi_bb72_7, phi_bb72_11, phi_bb72_12, phi_bb72_13, phi_bb72_14, phi_bb72_15, phi_bb72_18}, &block77, std::vector<Node*>{phi_bb72_5, phi_bb72_7, phi_bb72_11, phi_bb72_12, phi_bb72_13, phi_bb72_14, phi_bb72_15, phi_bb72_18});
  }

  TNode<Smi> phi_bb76_5;
  TNode<JSArray> phi_bb76_7;
  TNode<BoolT> phi_bb76_11;
  TNode<BoolT> phi_bb76_12;
  TNode<BoolT> phi_bb76_13;
  TNode<Smi> phi_bb76_14;
  TNode<Smi> phi_bb76_15;
  TNode<Smi> phi_bb76_18;
  TNode<IntPtrT> tmp91;
  TNode<FixedDoubleArray> tmp92;
  TNode<JSArray> tmp93;
  TNode<Smi> tmp94;
  if (block76.is_used()) {
    ca_.Bind(&block76, &phi_bb76_5, &phi_bb76_7, &phi_bb76_11, &phi_bb76_12, &phi_bb76_13, &phi_bb76_14, &phi_bb76_15, &phi_bb76_18);
    tmp91 = CodeStubAssembler(state_).SmiUntag(TNode<Smi>{tmp80});
    tmp92 = CodeStubAssembler(state_).AllocateFixedDoubleArrayWithHoles(TNode<IntPtrT>{tmp91}, CodeStubAssembler::AllocationFlag::kAllowLargeObjectAllocation);
    tmp93 = NewJSArray_0(state_, TNode<Context>{p_context}, TNode<Map>{tmp89}, TNode<FixedArrayBase>{tmp5});
    tmp94 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    ca_.Goto(&block81, phi_bb76_5, phi_bb76_7, phi_bb76_11, phi_bb76_12, phi_bb76_13, phi_bb76_14, phi_bb76_15, phi_bb76_18, tmp94);
  }

  TNode<Smi> phi_bb81_5;
  TNode<JSArray> phi_bb81_7;
  TNode<BoolT> phi_bb81_11;
  TNode<BoolT> phi_bb81_12;
  TNode<BoolT> phi_bb81_13;
  TNode<Smi> phi_bb81_14;
  TNode<Smi> phi_bb81_15;
  TNode<Smi> phi_bb81_18;
  TNode<Smi> phi_bb81_24;
  TNode<BoolT> tmp95;
  if (block81.is_used()) {
    ca_.Bind(&block81, &phi_bb81_5, &phi_bb81_7, &phi_bb81_11, &phi_bb81_12, &phi_bb81_13, &phi_bb81_14, &phi_bb81_15, &phi_bb81_18, &phi_bb81_24);
    tmp95 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb81_24}, TNode<Smi>{phi_bb81_18});
    ca_.Branch(tmp95, &block79, std::vector<Node*>{phi_bb81_5, phi_bb81_7, phi_bb81_11, phi_bb81_12, phi_bb81_13, phi_bb81_14, phi_bb81_15, phi_bb81_18, phi_bb81_24}, &block80, std::vector<Node*>{phi_bb81_5, phi_bb81_7, phi_bb81_11, phi_bb81_12, phi_bb81_13, phi_bb81_14, phi_bb81_15, phi_bb81_18, phi_bb81_24});
  }

  TNode<Smi> phi_bb79_5;
  TNode<JSArray> phi_bb79_7;
  TNode<BoolT> phi_bb79_11;
  TNode<BoolT> phi_bb79_12;
  TNode<BoolT> phi_bb79_13;
  TNode<Smi> phi_bb79_14;
  TNode<Smi> phi_bb79_15;
  TNode<Smi> phi_bb79_18;
  TNode<Smi> phi_bb79_24;
  TNode<IntPtrT> tmp96;
  TNode<IntPtrT> tmp97;
  TNode<IntPtrT> tmp98;
  TNode<Smi> tmp99;
  TNode<IntPtrT> tmp100;
  TNode<IntPtrT> tmp101;
  TNode<UintPtrT> tmp102;
  TNode<UintPtrT> tmp103;
  TNode<BoolT> tmp104;
  if (block79.is_used()) {
    ca_.Bind(&block79, &phi_bb79_5, &phi_bb79_7, &phi_bb79_11, &phi_bb79_12, &phi_bb79_13, &phi_bb79_14, &phi_bb79_15, &phi_bb79_18, &phi_bb79_24);
    tmp96 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp97 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp98 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp99 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp5, tmp98});
    tmp100 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp99});
    tmp101 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb79_24});
    tmp102 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp101});
    tmp103 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp100});
    tmp104 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp102}, TNode<UintPtrT>{tmp103});
    ca_.Branch(tmp104, &block87, std::vector<Node*>{phi_bb79_5, phi_bb79_7, phi_bb79_11, phi_bb79_12, phi_bb79_13, phi_bb79_14, phi_bb79_15, phi_bb79_18, phi_bb79_24, phi_bb79_24, phi_bb79_24}, &block88, std::vector<Node*>{phi_bb79_5, phi_bb79_7, phi_bb79_11, phi_bb79_12, phi_bb79_13, phi_bb79_14, phi_bb79_15, phi_bb79_18, phi_bb79_24, phi_bb79_24, phi_bb79_24});
  }

  TNode<Smi> phi_bb87_5;
  TNode<JSArray> phi_bb87_7;
  TNode<BoolT> phi_bb87_11;
  TNode<BoolT> phi_bb87_12;
  TNode<BoolT> phi_bb87_13;
  TNode<Smi> phi_bb87_14;
  TNode<Smi> phi_bb87_15;
  TNode<Smi> phi_bb87_18;
  TNode<Smi> phi_bb87_24;
  TNode<Smi> phi_bb87_29;
  TNode<Smi> phi_bb87_30;
  TNode<IntPtrT> tmp105;
  TNode<IntPtrT> tmp106;
  TNode<IntPtrT> tmp107;
  TNode<HeapObject> tmp108;
  TNode<IntPtrT> tmp109;
  TNode<Object> tmp110;
  TNode<Object> tmp111;
  TNode<Number> tmp112;
  if (block87.is_used()) {
    ca_.Bind(&block87, &phi_bb87_5, &phi_bb87_7, &phi_bb87_11, &phi_bb87_12, &phi_bb87_13, &phi_bb87_14, &phi_bb87_15, &phi_bb87_18, &phi_bb87_24, &phi_bb87_29, &phi_bb87_30);
    tmp105 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp106 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp101}, TNode<IntPtrT>{tmp105});
    tmp107 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp96}, TNode<IntPtrT>{tmp106});
    std::tie(tmp108, tmp109) = NewReference_Object_0(state_, TNode<HeapObject>{tmp5}, TNode<IntPtrT>{tmp107}).Flatten();
    tmp110 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp108, tmp109});
    tmp111 = UnsafeCast_HeapNumber_OR_Smi_OR_TheHole_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp110});
    compiler::CodeAssemblerLabel label113(&ca_);
    tmp112 = Cast_Number_0(state_, TNode<Object>{tmp111}, &label113);
    ca_.Goto(&block92, phi_bb87_5, phi_bb87_7, phi_bb87_11, phi_bb87_12, phi_bb87_13, phi_bb87_14, phi_bb87_15, phi_bb87_18, phi_bb87_24);
    if (label113.is_used()) {
      ca_.Bind(&label113);
      ca_.Goto(&block93, phi_bb87_5, phi_bb87_7, phi_bb87_11, phi_bb87_12, phi_bb87_13, phi_bb87_14, phi_bb87_15, phi_bb87_18, phi_bb87_24);
    }
  }

  TNode<Smi> phi_bb88_5;
  TNode<JSArray> phi_bb88_7;
  TNode<BoolT> phi_bb88_11;
  TNode<BoolT> phi_bb88_12;
  TNode<BoolT> phi_bb88_13;
  TNode<Smi> phi_bb88_14;
  TNode<Smi> phi_bb88_15;
  TNode<Smi> phi_bb88_18;
  TNode<Smi> phi_bb88_24;
  TNode<Smi> phi_bb88_29;
  TNode<Smi> phi_bb88_30;
  if (block88.is_used()) {
    ca_.Bind(&block88, &phi_bb88_5, &phi_bb88_7, &phi_bb88_11, &phi_bb88_12, &phi_bb88_13, &phi_bb88_14, &phi_bb88_15, &phi_bb88_18, &phi_bb88_24, &phi_bb88_29, &phi_bb88_30);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb93_5;
  TNode<JSArray> phi_bb93_7;
  TNode<BoolT> phi_bb93_11;
  TNode<BoolT> phi_bb93_12;
  TNode<BoolT> phi_bb93_13;
  TNode<Smi> phi_bb93_14;
  TNode<Smi> phi_bb93_15;
  TNode<Smi> phi_bb93_18;
  TNode<Smi> phi_bb93_24;
  if (block93.is_used()) {
    ca_.Bind(&block93, &phi_bb93_5, &phi_bb93_7, &phi_bb93_11, &phi_bb93_12, &phi_bb93_13, &phi_bb93_14, &phi_bb93_15, &phi_bb93_18, &phi_bb93_24);
    ca_.Goto(&block90, phi_bb93_5, phi_bb93_7, phi_bb93_11, phi_bb93_12, phi_bb93_13, phi_bb93_14, phi_bb93_15, phi_bb93_18, phi_bb93_24);
  }

  TNode<Smi> phi_bb92_5;
  TNode<JSArray> phi_bb92_7;
  TNode<BoolT> phi_bb92_11;
  TNode<BoolT> phi_bb92_12;
  TNode<BoolT> phi_bb92_13;
  TNode<Smi> phi_bb92_14;
  TNode<Smi> phi_bb92_15;
  TNode<Smi> phi_bb92_18;
  TNode<Smi> phi_bb92_24;
  TNode<IntPtrT> tmp114;
  TNode<IntPtrT> tmp115;
  TNode<IntPtrT> tmp116;
  TNode<Smi> tmp117;
  TNode<IntPtrT> tmp118;
  TNode<IntPtrT> tmp119;
  TNode<UintPtrT> tmp120;
  TNode<UintPtrT> tmp121;
  TNode<BoolT> tmp122;
  if (block92.is_used()) {
    ca_.Bind(&block92, &phi_bb92_5, &phi_bb92_7, &phi_bb92_11, &phi_bb92_12, &phi_bb92_13, &phi_bb92_14, &phi_bb92_15, &phi_bb92_18, &phi_bb92_24);
    tmp114 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp115 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp116 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp117 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp92, tmp116});
    tmp118 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp117});
    tmp119 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb92_24});
    tmp120 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp119});
    tmp121 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp118});
    tmp122 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp120}, TNode<UintPtrT>{tmp121});
    ca_.Branch(tmp122, &block98, std::vector<Node*>{phi_bb92_5, phi_bb92_7, phi_bb92_11, phi_bb92_12, phi_bb92_13, phi_bb92_14, phi_bb92_15, phi_bb92_18, phi_bb92_24, phi_bb92_24, phi_bb92_24}, &block99, std::vector<Node*>{phi_bb92_5, phi_bb92_7, phi_bb92_11, phi_bb92_12, phi_bb92_13, phi_bb92_14, phi_bb92_15, phi_bb92_18, phi_bb92_24, phi_bb92_24, phi_bb92_24});
  }

  TNode<Smi> phi_bb98_5;
  TNode<JSArray> phi_bb98_7;
  TNode<BoolT> phi_bb98_11;
  TNode<BoolT> phi_bb98_12;
  TNode<BoolT> phi_bb98_13;
  TNode<Smi> phi_bb98_14;
  TNode<Smi> phi_bb98_15;
  TNode<Smi> phi_bb98_18;
  TNode<Smi> phi_bb98_24;
  TNode<Smi> phi_bb98_31;
  TNode<Smi> phi_bb98_32;
  TNode<IntPtrT> tmp123;
  TNode<IntPtrT> tmp124;
  TNode<IntPtrT> tmp125;
  TNode<HeapObject> tmp126;
  TNode<IntPtrT> tmp127;
  TNode<BoolT> tmp128;
  TNode<Float64T> tmp129;
  if (block98.is_used()) {
    ca_.Bind(&block98, &phi_bb98_5, &phi_bb98_7, &phi_bb98_11, &phi_bb98_12, &phi_bb98_13, &phi_bb98_14, &phi_bb98_15, &phi_bb98_18, &phi_bb98_24, &phi_bb98_31, &phi_bb98_32);
    tmp123 = FromConstexpr_intptr_constexpr_int31_0(state_, kDoubleSize);
    tmp124 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp119}, TNode<IntPtrT>{tmp123});
    tmp125 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp114}, TNode<IntPtrT>{tmp124});
    std::tie(tmp126, tmp127) = NewReference_float64_or_hole_0(state_, TNode<HeapObject>{tmp92}, TNode<IntPtrT>{tmp125}).Flatten();
    std::tie(tmp128, tmp129) = Convert_float64_or_hole_Number_0(state_, TNode<Number>{tmp112}).Flatten();
    StoreFloat64OrHole_0(state_, TorqueStructReference_float64_or_hole_0{TNode<HeapObject>{tmp126}, TNode<IntPtrT>{tmp127}, TorqueStructUnsafe_0{}}, TorqueStructfloat64_or_hole_0{TNode<BoolT>{tmp128}, TNode<Float64T>{tmp129}});
    ca_.Goto(&block90, phi_bb98_5, phi_bb98_7, phi_bb98_11, phi_bb98_12, phi_bb98_13, phi_bb98_14, phi_bb98_15, phi_bb98_18, phi_bb98_24);
  }

  TNode<Smi> phi_bb99_5;
  TNode<JSArray> phi_bb99_7;
  TNode<BoolT> phi_bb99_11;
  TNode<BoolT> phi_bb99_12;
  TNode<BoolT> phi_bb99_13;
  TNode<Smi> phi_bb99_14;
  TNode<Smi> phi_bb99_15;
  TNode<Smi> phi_bb99_18;
  TNode<Smi> phi_bb99_24;
  TNode<Smi> phi_bb99_31;
  TNode<Smi> phi_bb99_32;
  if (block99.is_used()) {
    ca_.Bind(&block99, &phi_bb99_5, &phi_bb99_7, &phi_bb99_11, &phi_bb99_12, &phi_bb99_13, &phi_bb99_14, &phi_bb99_15, &phi_bb99_18, &phi_bb99_24, &phi_bb99_31, &phi_bb99_32);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb90_5;
  TNode<JSArray> phi_bb90_7;
  TNode<BoolT> phi_bb90_11;
  TNode<BoolT> phi_bb90_12;
  TNode<BoolT> phi_bb90_13;
  TNode<Smi> phi_bb90_14;
  TNode<Smi> phi_bb90_15;
  TNode<Smi> phi_bb90_18;
  TNode<Smi> phi_bb90_24;
  TNode<Smi> tmp130;
  TNode<Smi> tmp131;
  if (block90.is_used()) {
    ca_.Bind(&block90, &phi_bb90_5, &phi_bb90_7, &phi_bb90_11, &phi_bb90_12, &phi_bb90_13, &phi_bb90_14, &phi_bb90_15, &phi_bb90_18, &phi_bb90_24);
    tmp130 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp131 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb90_24}, TNode<Smi>{tmp130});
    ca_.Goto(&block81, phi_bb90_5, phi_bb90_7, phi_bb90_11, phi_bb90_12, phi_bb90_13, phi_bb90_14, phi_bb90_15, phi_bb90_18, tmp131);
  }

  TNode<Smi> phi_bb80_5;
  TNode<JSArray> phi_bb80_7;
  TNode<BoolT> phi_bb80_11;
  TNode<BoolT> phi_bb80_12;
  TNode<BoolT> phi_bb80_13;
  TNode<Smi> phi_bb80_14;
  TNode<Smi> phi_bb80_15;
  TNode<Smi> phi_bb80_18;
  TNode<Smi> phi_bb80_24;
  TNode<IntPtrT> tmp132;
  if (block80.is_used()) {
    ca_.Bind(&block80, &phi_bb80_5, &phi_bb80_7, &phi_bb80_11, &phi_bb80_12, &phi_bb80_13, &phi_bb80_14, &phi_bb80_15, &phi_bb80_18, &phi_bb80_24);
    tmp132 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    CodeStubAssembler(state_).StoreReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp93, tmp132}, tmp92);
    ca_.Goto(&block78, phi_bb80_5, phi_bb80_7, phi_bb80_11, phi_bb80_12, phi_bb80_13, phi_bb80_14, phi_bb80_15, phi_bb80_18, tmp93);
  }

  TNode<Smi> phi_bb77_5;
  TNode<JSArray> phi_bb77_7;
  TNode<BoolT> phi_bb77_11;
  TNode<BoolT> phi_bb77_12;
  TNode<BoolT> phi_bb77_13;
  TNode<Smi> phi_bb77_14;
  TNode<Smi> phi_bb77_15;
  TNode<Smi> phi_bb77_18;
  TNode<JSArray> tmp133;
  if (block77.is_used()) {
    ca_.Bind(&block77, &phi_bb77_5, &phi_bb77_7, &phi_bb77_11, &phi_bb77_12, &phi_bb77_13, &phi_bb77_14, &phi_bb77_15, &phi_bb77_18);
    tmp133 = NewJSArray_0(state_, TNode<Context>{p_context}, TNode<Map>{tmp89}, TNode<FixedArrayBase>{tmp5});
    ca_.Goto(&block78, phi_bb77_5, phi_bb77_7, phi_bb77_11, phi_bb77_12, phi_bb77_13, phi_bb77_14, phi_bb77_15, phi_bb77_18, tmp133);
  }

  TNode<Smi> phi_bb78_5;
  TNode<JSArray> phi_bb78_7;
  TNode<BoolT> phi_bb78_11;
  TNode<BoolT> phi_bb78_12;
  TNode<BoolT> phi_bb78_13;
  TNode<Smi> phi_bb78_14;
  TNode<Smi> phi_bb78_15;
  TNode<Smi> phi_bb78_18;
  TNode<JSArray> phi_bb78_22;
  TNode<FixedArray> tmp134;
  if (block78.is_used()) {
    ca_.Bind(&block78, &phi_bb78_5, &phi_bb78_7, &phi_bb78_11, &phi_bb78_12, &phi_bb78_13, &phi_bb78_14, &phi_bb78_15, &phi_bb78_18, &phi_bb78_22);
    tmp134 = kEmptyFixedArray_0(state_);
    *label_Bailout_parameter_1 = phi_bb78_14;
    *label_Bailout_parameter_0 = phi_bb78_22;
    ca_.Goto(label_Bailout);
  }

  TNode<Smi> phi_bb106_5;
  TNode<JSArray> phi_bb106_7;
  TNode<BoolT> phi_bb106_11;
  TNode<BoolT> phi_bb106_12;
  TNode<BoolT> phi_bb106_13;
  if (block106.is_used()) {
    ca_.Bind(&block106, &phi_bb106_5, &phi_bb106_7, &phi_bb106_11, &phi_bb106_12, &phi_bb106_13);
    ca_.Branch(phi_bb106_12, &block108, std::vector<Node*>{phi_bb106_5, phi_bb106_7, phi_bb106_11, phi_bb106_12, phi_bb106_13}, &block109, std::vector<Node*>{phi_bb106_5, phi_bb106_7, phi_bb106_11, phi_bb106_12, phi_bb106_13});
  }

  TNode<Smi> phi_bb108_5;
  TNode<JSArray> phi_bb108_7;
  TNode<BoolT> phi_bb108_11;
  TNode<BoolT> phi_bb108_12;
  TNode<BoolT> phi_bb108_13;
  TNode<Int32T> tmp135;
  if (block108.is_used()) {
    ca_.Bind(&block108, &phi_bb108_5, &phi_bb108_7, &phi_bb108_11, &phi_bb108_12, &phi_bb108_13);
    tmp135 = FromConstexpr_ElementsKind_constexpr_PACKED_DOUBLE_ELEMENTS_0(state_, ElementsKind::PACKED_DOUBLE_ELEMENTS);
    ca_.Goto(&block110, phi_bb108_5, phi_bb108_7, phi_bb108_11, phi_bb108_12, phi_bb108_13, tmp135);
  }

  TNode<Smi> phi_bb109_5;
  TNode<JSArray> phi_bb109_7;
  TNode<BoolT> phi_bb109_11;
  TNode<BoolT> phi_bb109_12;
  TNode<BoolT> phi_bb109_13;
  TNode<Int32T> tmp136;
  if (block109.is_used()) {
    ca_.Bind(&block109, &phi_bb109_5, &phi_bb109_7, &phi_bb109_11, &phi_bb109_12, &phi_bb109_13);
    tmp136 = FromConstexpr_ElementsKind_constexpr_PACKED_ELEMENTS_0(state_, ElementsKind::PACKED_ELEMENTS);
    ca_.Goto(&block110, phi_bb109_5, phi_bb109_7, phi_bb109_11, phi_bb109_12, phi_bb109_13, tmp136);
  }

  TNode<Smi> phi_bb110_5;
  TNode<JSArray> phi_bb110_7;
  TNode<BoolT> phi_bb110_11;
  TNode<BoolT> phi_bb110_12;
  TNode<BoolT> phi_bb110_13;
  TNode<Int32T> phi_bb110_19;
  if (block110.is_used()) {
    ca_.Bind(&block110, &phi_bb110_5, &phi_bb110_7, &phi_bb110_11, &phi_bb110_12, &phi_bb110_13, &phi_bb110_19);
    ca_.Goto(&block107, phi_bb110_5, phi_bb110_7, phi_bb110_11, phi_bb110_12, phi_bb110_13, phi_bb110_19);
  }

  TNode<Smi> phi_bb107_5;
  TNode<JSArray> phi_bb107_7;
  TNode<BoolT> phi_bb107_11;
  TNode<BoolT> phi_bb107_12;
  TNode<BoolT> phi_bb107_13;
  TNode<Int32T> phi_bb107_19;
  if (block107.is_used()) {
    ca_.Bind(&block107, &phi_bb107_5, &phi_bb107_7, &phi_bb107_11, &phi_bb107_12, &phi_bb107_13, &phi_bb107_19);
    ca_.Branch(phi_bb107_13, &block113, std::vector<Node*>{phi_bb107_5, phi_bb107_7, phi_bb107_11, phi_bb107_12, phi_bb107_13, phi_bb107_19, phi_bb107_13}, &block114, std::vector<Node*>{phi_bb107_5, phi_bb107_7, phi_bb107_11, phi_bb107_12, phi_bb107_13, phi_bb107_19, phi_bb107_13});
  }

  TNode<Smi> phi_bb113_5;
  TNode<JSArray> phi_bb113_7;
  TNode<BoolT> phi_bb113_11;
  TNode<BoolT> phi_bb113_12;
  TNode<BoolT> phi_bb113_13;
  TNode<Int32T> phi_bb113_19;
  TNode<BoolT> phi_bb113_20;
  TNode<BoolT> tmp137;
  if (block113.is_used()) {
    ca_.Bind(&block113, &phi_bb113_5, &phi_bb113_7, &phi_bb113_11, &phi_bb113_12, &phi_bb113_13, &phi_bb113_19, &phi_bb113_20);
    tmp137 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block115, phi_bb113_5, phi_bb113_7, phi_bb113_11, phi_bb113_12, phi_bb113_13, phi_bb113_19, phi_bb113_20, tmp137);
  }

  TNode<Smi> phi_bb114_5;
  TNode<JSArray> phi_bb114_7;
  TNode<BoolT> phi_bb114_11;
  TNode<BoolT> phi_bb114_12;
  TNode<BoolT> phi_bb114_13;
  TNode<Int32T> phi_bb114_19;
  TNode<BoolT> phi_bb114_20;
  TNode<BoolT> tmp138;
  if (block114.is_used()) {
    ca_.Bind(&block114, &phi_bb114_5, &phi_bb114_7, &phi_bb114_11, &phi_bb114_12, &phi_bb114_13, &phi_bb114_19, &phi_bb114_20);
    tmp138 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{p_len}, TNode<Smi>{tmp76});
    ca_.Goto(&block115, phi_bb114_5, phi_bb114_7, phi_bb114_11, phi_bb114_12, phi_bb114_13, phi_bb114_19, phi_bb114_20, tmp138);
  }

  TNode<Smi> phi_bb115_5;
  TNode<JSArray> phi_bb115_7;
  TNode<BoolT> phi_bb115_11;
  TNode<BoolT> phi_bb115_12;
  TNode<BoolT> phi_bb115_13;
  TNode<Int32T> phi_bb115_19;
  TNode<BoolT> phi_bb115_20;
  TNode<BoolT> phi_bb115_21;
  if (block115.is_used()) {
    ca_.Bind(&block115, &phi_bb115_5, &phi_bb115_7, &phi_bb115_11, &phi_bb115_12, &phi_bb115_13, &phi_bb115_19, &phi_bb115_20, &phi_bb115_21);
    ca_.Branch(phi_bb115_21, &block111, std::vector<Node*>{phi_bb115_5, phi_bb115_7, phi_bb115_11, phi_bb115_12, phi_bb115_13, phi_bb115_19}, &block112, std::vector<Node*>{phi_bb115_5, phi_bb115_7, phi_bb115_11, phi_bb115_12, phi_bb115_13, phi_bb115_19});
  }

  TNode<Smi> phi_bb111_5;
  TNode<JSArray> phi_bb111_7;
  TNode<BoolT> phi_bb111_11;
  TNode<BoolT> phi_bb111_12;
  TNode<BoolT> phi_bb111_13;
  TNode<Int32T> phi_bb111_19;
  TNode<Int32T> tmp139;
  if (block111.is_used()) {
    ca_.Bind(&block111, &phi_bb111_5, &phi_bb111_7, &phi_bb111_11, &phi_bb111_12, &phi_bb111_13, &phi_bb111_19);
    tmp139 = FastHoleyElementsKind_0(state_, TNode<Int32T>{phi_bb111_19});
    ca_.Goto(&block112, phi_bb111_5, phi_bb111_7, phi_bb111_11, phi_bb111_12, phi_bb111_13, tmp139);
  }

  TNode<Smi> phi_bb112_5;
  TNode<JSArray> phi_bb112_7;
  TNode<BoolT> phi_bb112_11;
  TNode<BoolT> phi_bb112_12;
  TNode<BoolT> phi_bb112_13;
  TNode<Int32T> phi_bb112_19;
  TNode<NativeContext> tmp140;
  TNode<Map> tmp141;
  TNode<BoolT> tmp142;
  if (block112.is_used()) {
    ca_.Bind(&block112, &phi_bb112_5, &phi_bb112_7, &phi_bb112_11, &phi_bb112_12, &phi_bb112_13, &phi_bb112_19);
    tmp140 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{p_context});
    tmp141 = CodeStubAssembler(state_).LoadJSArrayElementsMap(TNode<Int32T>{phi_bb112_19}, TNode<NativeContext>{tmp140});
    tmp142 = CodeStubAssembler(state_).IsDoubleElementsKind(TNode<Int32T>{phi_bb112_19});
    ca_.Branch(tmp142, &block116, std::vector<Node*>{phi_bb112_5, phi_bb112_7, phi_bb112_11, phi_bb112_12, phi_bb112_13}, &block117, std::vector<Node*>{phi_bb112_5, phi_bb112_7, phi_bb112_11, phi_bb112_12, phi_bb112_13});
  }

  TNode<Smi> phi_bb116_5;
  TNode<JSArray> phi_bb116_7;
  TNode<BoolT> phi_bb116_11;
  TNode<BoolT> phi_bb116_12;
  TNode<BoolT> phi_bb116_13;
  TNode<IntPtrT> tmp143;
  TNode<FixedDoubleArray> tmp144;
  TNode<JSArray> tmp145;
  TNode<Smi> tmp146;
  if (block116.is_used()) {
    ca_.Bind(&block116, &phi_bb116_5, &phi_bb116_7, &phi_bb116_11, &phi_bb116_12, &phi_bb116_13);
    tmp143 = CodeStubAssembler(state_).SmiUntag(TNode<Smi>{tmp76});
    tmp144 = CodeStubAssembler(state_).AllocateFixedDoubleArrayWithHoles(TNode<IntPtrT>{tmp143}, CodeStubAssembler::AllocationFlag::kAllowLargeObjectAllocation);
    tmp145 = NewJSArray_0(state_, TNode<Context>{p_context}, TNode<Map>{tmp141}, TNode<FixedArrayBase>{tmp5});
    tmp146 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    ca_.Goto(&block121, phi_bb116_5, phi_bb116_7, phi_bb116_11, phi_bb116_12, phi_bb116_13, tmp146);
  }

  TNode<Smi> phi_bb121_5;
  TNode<JSArray> phi_bb121_7;
  TNode<BoolT> phi_bb121_11;
  TNode<BoolT> phi_bb121_12;
  TNode<BoolT> phi_bb121_13;
  TNode<Smi> phi_bb121_23;
  TNode<BoolT> tmp147;
  if (block121.is_used()) {
    ca_.Bind(&block121, &phi_bb121_5, &phi_bb121_7, &phi_bb121_11, &phi_bb121_12, &phi_bb121_13, &phi_bb121_23);
    tmp147 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb121_23}, TNode<Smi>{p_len});
    ca_.Branch(tmp147, &block119, std::vector<Node*>{phi_bb121_5, phi_bb121_7, phi_bb121_11, phi_bb121_12, phi_bb121_13, phi_bb121_23}, &block120, std::vector<Node*>{phi_bb121_5, phi_bb121_7, phi_bb121_11, phi_bb121_12, phi_bb121_13, phi_bb121_23});
  }

  TNode<Smi> phi_bb119_5;
  TNode<JSArray> phi_bb119_7;
  TNode<BoolT> phi_bb119_11;
  TNode<BoolT> phi_bb119_12;
  TNode<BoolT> phi_bb119_13;
  TNode<Smi> phi_bb119_23;
  TNode<IntPtrT> tmp148;
  TNode<IntPtrT> tmp149;
  TNode<IntPtrT> tmp150;
  TNode<Smi> tmp151;
  TNode<IntPtrT> tmp152;
  TNode<IntPtrT> tmp153;
  TNode<UintPtrT> tmp154;
  TNode<UintPtrT> tmp155;
  TNode<BoolT> tmp156;
  if (block119.is_used()) {
    ca_.Bind(&block119, &phi_bb119_5, &phi_bb119_7, &phi_bb119_11, &phi_bb119_12, &phi_bb119_13, &phi_bb119_23);
    tmp148 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp149 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp150 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp151 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp5, tmp150});
    tmp152 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp151});
    tmp153 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb119_23});
    tmp154 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp153});
    tmp155 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp152});
    tmp156 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp154}, TNode<UintPtrT>{tmp155});
    ca_.Branch(tmp156, &block127, std::vector<Node*>{phi_bb119_5, phi_bb119_7, phi_bb119_11, phi_bb119_12, phi_bb119_13, phi_bb119_23, phi_bb119_23, phi_bb119_23}, &block128, std::vector<Node*>{phi_bb119_5, phi_bb119_7, phi_bb119_11, phi_bb119_12, phi_bb119_13, phi_bb119_23, phi_bb119_23, phi_bb119_23});
  }

  TNode<Smi> phi_bb127_5;
  TNode<JSArray> phi_bb127_7;
  TNode<BoolT> phi_bb127_11;
  TNode<BoolT> phi_bb127_12;
  TNode<BoolT> phi_bb127_13;
  TNode<Smi> phi_bb127_23;
  TNode<Smi> phi_bb127_28;
  TNode<Smi> phi_bb127_29;
  TNode<IntPtrT> tmp157;
  TNode<IntPtrT> tmp158;
  TNode<IntPtrT> tmp159;
  TNode<HeapObject> tmp160;
  TNode<IntPtrT> tmp161;
  TNode<Object> tmp162;
  TNode<Object> tmp163;
  TNode<Number> tmp164;
  if (block127.is_used()) {
    ca_.Bind(&block127, &phi_bb127_5, &phi_bb127_7, &phi_bb127_11, &phi_bb127_12, &phi_bb127_13, &phi_bb127_23, &phi_bb127_28, &phi_bb127_29);
    tmp157 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp158 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp153}, TNode<IntPtrT>{tmp157});
    tmp159 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp148}, TNode<IntPtrT>{tmp158});
    std::tie(tmp160, tmp161) = NewReference_Object_0(state_, TNode<HeapObject>{tmp5}, TNode<IntPtrT>{tmp159}).Flatten();
    tmp162 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp160, tmp161});
    tmp163 = UnsafeCast_HeapNumber_OR_Smi_OR_TheHole_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp162});
    compiler::CodeAssemblerLabel label165(&ca_);
    tmp164 = Cast_Number_0(state_, TNode<Object>{tmp163}, &label165);
    ca_.Goto(&block132, phi_bb127_5, phi_bb127_7, phi_bb127_11, phi_bb127_12, phi_bb127_13, phi_bb127_23);
    if (label165.is_used()) {
      ca_.Bind(&label165);
      ca_.Goto(&block133, phi_bb127_5, phi_bb127_7, phi_bb127_11, phi_bb127_12, phi_bb127_13, phi_bb127_23);
    }
  }

  TNode<Smi> phi_bb128_5;
  TNode<JSArray> phi_bb128_7;
  TNode<BoolT> phi_bb128_11;
  TNode<BoolT> phi_bb128_12;
  TNode<BoolT> phi_bb128_13;
  TNode<Smi> phi_bb128_23;
  TNode<Smi> phi_bb128_28;
  TNode<Smi> phi_bb128_29;
  if (block128.is_used()) {
    ca_.Bind(&block128, &phi_bb128_5, &phi_bb128_7, &phi_bb128_11, &phi_bb128_12, &phi_bb128_13, &phi_bb128_23, &phi_bb128_28, &phi_bb128_29);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb133_5;
  TNode<JSArray> phi_bb133_7;
  TNode<BoolT> phi_bb133_11;
  TNode<BoolT> phi_bb133_12;
  TNode<BoolT> phi_bb133_13;
  TNode<Smi> phi_bb133_23;
  if (block133.is_used()) {
    ca_.Bind(&block133, &phi_bb133_5, &phi_bb133_7, &phi_bb133_11, &phi_bb133_12, &phi_bb133_13, &phi_bb133_23);
    ca_.Goto(&block130, phi_bb133_5, phi_bb133_7, phi_bb133_11, phi_bb133_12, phi_bb133_13, phi_bb133_23);
  }

  TNode<Smi> phi_bb132_5;
  TNode<JSArray> phi_bb132_7;
  TNode<BoolT> phi_bb132_11;
  TNode<BoolT> phi_bb132_12;
  TNode<BoolT> phi_bb132_13;
  TNode<Smi> phi_bb132_23;
  TNode<IntPtrT> tmp166;
  TNode<IntPtrT> tmp167;
  TNode<IntPtrT> tmp168;
  TNode<Smi> tmp169;
  TNode<IntPtrT> tmp170;
  TNode<IntPtrT> tmp171;
  TNode<UintPtrT> tmp172;
  TNode<UintPtrT> tmp173;
  TNode<BoolT> tmp174;
  if (block132.is_used()) {
    ca_.Bind(&block132, &phi_bb132_5, &phi_bb132_7, &phi_bb132_11, &phi_bb132_12, &phi_bb132_13, &phi_bb132_23);
    tmp166 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp167 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp168 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp169 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp144, tmp168});
    tmp170 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp169});
    tmp171 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb132_23});
    tmp172 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp171});
    tmp173 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp170});
    tmp174 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp172}, TNode<UintPtrT>{tmp173});
    ca_.Branch(tmp174, &block138, std::vector<Node*>{phi_bb132_5, phi_bb132_7, phi_bb132_11, phi_bb132_12, phi_bb132_13, phi_bb132_23, phi_bb132_23, phi_bb132_23}, &block139, std::vector<Node*>{phi_bb132_5, phi_bb132_7, phi_bb132_11, phi_bb132_12, phi_bb132_13, phi_bb132_23, phi_bb132_23, phi_bb132_23});
  }

  TNode<Smi> phi_bb138_5;
  TNode<JSArray> phi_bb138_7;
  TNode<BoolT> phi_bb138_11;
  TNode<BoolT> phi_bb138_12;
  TNode<BoolT> phi_bb138_13;
  TNode<Smi> phi_bb138_23;
  TNode<Smi> phi_bb138_30;
  TNode<Smi> phi_bb138_31;
  TNode<IntPtrT> tmp175;
  TNode<IntPtrT> tmp176;
  TNode<IntPtrT> tmp177;
  TNode<HeapObject> tmp178;
  TNode<IntPtrT> tmp179;
  TNode<BoolT> tmp180;
  TNode<Float64T> tmp181;
  if (block138.is_used()) {
    ca_.Bind(&block138, &phi_bb138_5, &phi_bb138_7, &phi_bb138_11, &phi_bb138_12, &phi_bb138_13, &phi_bb138_23, &phi_bb138_30, &phi_bb138_31);
    tmp175 = FromConstexpr_intptr_constexpr_int31_0(state_, kDoubleSize);
    tmp176 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp171}, TNode<IntPtrT>{tmp175});
    tmp177 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp166}, TNode<IntPtrT>{tmp176});
    std::tie(tmp178, tmp179) = NewReference_float64_or_hole_0(state_, TNode<HeapObject>{tmp144}, TNode<IntPtrT>{tmp177}).Flatten();
    std::tie(tmp180, tmp181) = Convert_float64_or_hole_Number_0(state_, TNode<Number>{tmp164}).Flatten();
    StoreFloat64OrHole_0(state_, TorqueStructReference_float64_or_hole_0{TNode<HeapObject>{tmp178}, TNode<IntPtrT>{tmp179}, TorqueStructUnsafe_0{}}, TorqueStructfloat64_or_hole_0{TNode<BoolT>{tmp180}, TNode<Float64T>{tmp181}});
    ca_.Goto(&block130, phi_bb138_5, phi_bb138_7, phi_bb138_11, phi_bb138_12, phi_bb138_13, phi_bb138_23);
  }

  TNode<Smi> phi_bb139_5;
  TNode<JSArray> phi_bb139_7;
  TNode<BoolT> phi_bb139_11;
  TNode<BoolT> phi_bb139_12;
  TNode<BoolT> phi_bb139_13;
  TNode<Smi> phi_bb139_23;
  TNode<Smi> phi_bb139_30;
  TNode<Smi> phi_bb139_31;
  if (block139.is_used()) {
    ca_.Bind(&block139, &phi_bb139_5, &phi_bb139_7, &phi_bb139_11, &phi_bb139_12, &phi_bb139_13, &phi_bb139_23, &phi_bb139_30, &phi_bb139_31);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb130_5;
  TNode<JSArray> phi_bb130_7;
  TNode<BoolT> phi_bb130_11;
  TNode<BoolT> phi_bb130_12;
  TNode<BoolT> phi_bb130_13;
  TNode<Smi> phi_bb130_23;
  TNode<Smi> tmp182;
  TNode<Smi> tmp183;
  if (block130.is_used()) {
    ca_.Bind(&block130, &phi_bb130_5, &phi_bb130_7, &phi_bb130_11, &phi_bb130_12, &phi_bb130_13, &phi_bb130_23);
    tmp182 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp183 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb130_23}, TNode<Smi>{tmp182});
    ca_.Goto(&block121, phi_bb130_5, phi_bb130_7, phi_bb130_11, phi_bb130_12, phi_bb130_13, tmp183);
  }

  TNode<Smi> phi_bb120_5;
  TNode<JSArray> phi_bb120_7;
  TNode<BoolT> phi_bb120_11;
  TNode<BoolT> phi_bb120_12;
  TNode<BoolT> phi_bb120_13;
  TNode<Smi> phi_bb120_23;
  TNode<IntPtrT> tmp184;
  if (block120.is_used()) {
    ca_.Bind(&block120, &phi_bb120_5, &phi_bb120_7, &phi_bb120_11, &phi_bb120_12, &phi_bb120_13, &phi_bb120_23);
    tmp184 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    CodeStubAssembler(state_).StoreReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp145, tmp184}, tmp144);
    ca_.Goto(&block118, phi_bb120_5, phi_bb120_7, phi_bb120_11, phi_bb120_12, phi_bb120_13, tmp145);
  }

  TNode<Smi> phi_bb117_5;
  TNode<JSArray> phi_bb117_7;
  TNode<BoolT> phi_bb117_11;
  TNode<BoolT> phi_bb117_12;
  TNode<BoolT> phi_bb117_13;
  TNode<JSArray> tmp185;
  if (block117.is_used()) {
    ca_.Bind(&block117, &phi_bb117_5, &phi_bb117_7, &phi_bb117_11, &phi_bb117_12, &phi_bb117_13);
    tmp185 = NewJSArray_0(state_, TNode<Context>{p_context}, TNode<Map>{tmp141}, TNode<FixedArrayBase>{tmp5});
    ca_.Goto(&block118, phi_bb117_5, phi_bb117_7, phi_bb117_11, phi_bb117_12, phi_bb117_13, tmp185);
  }

  TNode<Smi> phi_bb118_5;
  TNode<JSArray> phi_bb118_7;
  TNode<BoolT> phi_bb118_11;
  TNode<BoolT> phi_bb118_12;
  TNode<BoolT> phi_bb118_13;
  TNode<JSArray> phi_bb118_21;
  TNode<FixedArray> tmp186;
  if (block118.is_used()) {
    ca_.Bind(&block118, &phi_bb118_5, &phi_bb118_7, &phi_bb118_11, &phi_bb118_12, &phi_bb118_13, &phi_bb118_21);
    tmp186 = kEmptyFixedArray_0(state_);
    ca_.Goto(&block141, phi_bb118_21);
  }

  TNode<JSArray> phi_bb141_5;
    ca_.Bind(&block141, &phi_bb141_5);
  return TNode<JSArray>{phi_bb141_5};
}

TF_BUILTIN(ArrayMap, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  Node* argc = Parameter(Descriptor::kJSActualArgumentsCount);
  TNode<IntPtrT> arguments_length(ChangeInt32ToIntPtr(UncheckedCast<Int32T>(argc)));
  TNode<RawPtrT> arguments_frame = UncheckedCast<RawPtrT>(LoadFramePointer());
  TorqueStructArguments torque_arguments(GetFrameArguments(arguments_frame, arguments_length));
  CodeStubArguments arguments(this, torque_arguments);
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = arguments.GetReceiver();
USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSReceiver, Number> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    ca_.Goto(&block0);

  TNode<Object> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<Number> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<BoolT> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = RequireObjectCoercible_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, "Array.prototype.map");
    tmp1 = CodeStubAssembler(state_).ToObject_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp2 = GetLengthProperty_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp4 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{tmp3});
    ca_.Branch(tmp4, &block3, std::vector<Node*>{}, &block4, std::vector<Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block2);
  }

  TNode<IntPtrT> tmp5;
  TNode<Object> tmp6;
  TNode<JSReceiver> tmp7;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp5 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp6 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{tmp5});
    compiler::CodeAssemblerLabel label8(&ca_);
    tmp7 = Cast_Callable_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp6}, &label8);
    ca_.Goto(&block5);
    if (label8.is_used()) {
      ca_.Bind(&label8);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block2);
  }

  TNode<IntPtrT> tmp9;
  TNode<Object> tmp10;
  TNode<Number> tmp11;
  TNode<BoolT> tmp12;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp10 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{tmp9});
    tmp11 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp12 = CodeStubAssembler(state_).IsArraySpeciesProtectorCellInvalid();
    ca_.Branch(tmp12, &block11, std::vector<Node*>{}, &block12, std::vector<Node*>{});
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    ca_.Goto(&block10);
  }

  TNode<JSArray> tmp13;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    compiler::CodeAssemblerLabel label14(&ca_);
    tmp13 = Cast_FastJSArrayForRead_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label14);
    ca_.Goto(&block13);
    if (label14.is_used()) {
      ca_.Bind(&label14);
      ca_.Goto(&block14);
    }
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    ca_.Goto(&block10);
  }

  TNode<Smi> tmp15;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    compiler::CodeAssemblerLabel label16(&ca_);
    tmp15 = Cast_Smi_0(state_, TNode<Object>{tmp2}, &label16);
    ca_.Goto(&block15);
    if (label16.is_used()) {
      ca_.Bind(&label16);
      ca_.Goto(&block16);
    }
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    ca_.Goto(&block10);
  }

  TNode<JSArray> tmp17;
    compiler::TypedCodeAssemblerVariable<JSArray> tmp19(&ca_);
    compiler::TypedCodeAssemblerVariable<Smi> tmp20(&ca_);
  if (block15.is_used()) {
    ca_.Bind(&block15);
    compiler::CodeAssemblerLabel label18(&ca_);
    tmp17 = FastArrayMap_0(state_, TNode<Context>{parameter0}, TNode<JSArray>{tmp13}, TNode<Smi>{tmp15}, TNode<JSReceiver>{tmp7}, TNode<Object>{tmp10}, &label18, &tmp19, &tmp20);
    ca_.Goto(&block17);
    if (label18.is_used()) {
      ca_.Bind(&label18);
      ca_.Goto(&block18);
    }
  }

  if (block18.is_used()) {
    ca_.Bind(&block18);
    ca_.Goto(&block7, tmp19.value(), tmp20.value());
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    arguments.PopAndReturn(tmp17);
  }

  TNode<JSReceiver> tmp21;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp21 = CodeStubAssembler(state_).ArraySpeciesCreate(TNode<Context>{parameter0}, TNode<Object>{parameter1}, TNode<Number>{tmp2});
    ca_.Goto(&block7, tmp21, tmp11);
  }

  TNode<JSReceiver> phi_bb7_9;
  TNode<Number> phi_bb7_10;
  TNode<Object> tmp22;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_9, &phi_bb7_10);
    tmp22 = CodeStubAssembler(state_).CallBuiltin(Builtins::kArrayMapLoopContinuation, parameter0, tmp1, tmp7, tmp10, phi_bb7_9, tmp1, phi_bb7_10, tmp2);
    arguments.PopAndReturn(tmp22);
  }

  TNode<IntPtrT> tmp23;
  TNode<Object> tmp24;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp23 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp24 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{tmp23});
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, MessageTemplate::kCalledNonCallable, TNode<Object>{tmp24});
  }
}

TNode<Object> UnsafeCast_HeapNumber_OR_Smi_OR_TheHole_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Object> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = (TNode<Object>{p_o});
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
  return TNode<Object>{tmp0};
}

TNode<JSArray> Cast_FastJSArrayForRead_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError) {
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

  TNode<JSArray> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_FastJSArrayForRead_0(state_, TNode<Context>{p_context}, TNode<HeapObject>{tmp0}, &label3);
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
  return TNode<JSArray>{tmp2};
}

}  // namespace internal
}  // namespace v8

