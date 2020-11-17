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

TF_BUILTIN(ArrayFindIndexLoopEagerDeoptContinuation, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kReceiver));
USE(parameter1);
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::kCallback));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::kThisArg));
  USE(parameter3);
  TNode<Object> parameter4 = UncheckedCast<Object>(Parameter(Descriptor::kInitialK));
  USE(parameter4);
  TNode<Object> parameter5 = UncheckedCast<Object>(Parameter(Descriptor::kLength));
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
    tmp8 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kArrayFindIndexLoopContinuation, parameter0, tmp0, tmp2, parameter3, tmp0, tmp4, tmp6));
    CodeStubAssembler(state_).Return(tmp8);
  }
}

TF_BUILTIN(ArrayFindIndexLoopLazyDeoptContinuation, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kReceiver));
USE(parameter1);
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::kCallback));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::kThisArg));
  USE(parameter3);
  TNode<Object> parameter4 = UncheckedCast<Object>(Parameter(Descriptor::kInitialK));
  USE(parameter4);
  TNode<Object> parameter5 = UncheckedCast<Object>(Parameter(Descriptor::kLength));
  USE(parameter5);
  TNode<Object> parameter6 = UncheckedCast<Object>(Parameter(Descriptor::kResult));
  USE(parameter6);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    CodeStubAssembler(state_).Unreachable();
  }
}

TF_BUILTIN(ArrayFindIndexLoopAfterCallbackLazyDeoptContinuation, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kReceiver));
USE(parameter1);
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::kCallback));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::kThisArg));
  USE(parameter3);
  TNode<Object> parameter4 = UncheckedCast<Object>(Parameter(Descriptor::kInitialK));
  USE(parameter4);
  TNode<Object> parameter5 = UncheckedCast<Object>(Parameter(Descriptor::kLength));
  USE(parameter5);
  TNode<Object> parameter6 = UncheckedCast<Object>(Parameter(Descriptor::kFoundValue));
  USE(parameter6);
  TNode<Object> parameter7 = UncheckedCast<Object>(Parameter(Descriptor::kIsFound));
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
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
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

  TNode<BoolT> tmp8;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp8 = ToBoolean_0(state_, TNode<Object>{parameter7});
    ca_.Branch(tmp8, &block17, std::vector<Node*>{}, &block18, std::vector<Node*>{});
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    CodeStubAssembler(state_).Return(parameter6);
  }

  TNode<Number> tmp9;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp9 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kArrayFindIndexLoopContinuation, parameter0, tmp0, tmp2, parameter3, tmp0, tmp4, tmp6));
    CodeStubAssembler(state_).Return(tmp9);
  }
}

TF_BUILTIN(ArrayFindIndexLoopContinuation, CodeStubAssembler) {
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
  TNode<Number> parameter5 = UncheckedCast<Number>(Parameter(Descriptor::ParameterIndex<4>()));
  USE(parameter5);
  TNode<Number> parameter6 = UncheckedCast<Number>(Parameter(Descriptor::ParameterIndex<5>()));
  USE(parameter6);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    ca_.Goto(&block3, parameter5);
  }

  TNode<Number> phi_bb3_7;
  TNode<BoolT> tmp0;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_7);
    tmp0 = NumberIsLessThan_0(state_, TNode<Number>{phi_bb3_7}, TNode<Number>{parameter6});
    ca_.Branch(tmp0, &block1, std::vector<Node*>{phi_bb3_7}, &block2, std::vector<Node*>{phi_bb3_7});
  }

  TNode<Number> phi_bb1_7;
  TNode<Object> tmp1;
  TNode<Object> tmp2;
  TNode<BoolT> tmp3;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_7);
    tmp1 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<Object>{parameter4}, TNode<Object>{phi_bb1_7});
    tmp2 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<Object>{parameter2}, TNode<Object>{parameter3}, TNode<Object>{tmp1}, TNode<Object>{phi_bb1_7}, TNode<Object>{parameter4});
    tmp3 = ToBoolean_0(state_, TNode<Object>{tmp2});
    ca_.Branch(tmp3, &block5, std::vector<Node*>{phi_bb1_7}, &block6, std::vector<Node*>{phi_bb1_7});
  }

  TNode<Number> phi_bb5_7;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_7);
    CodeStubAssembler(state_).Return(phi_bb5_7);
  }

  TNode<Number> phi_bb6_7;
  TNode<Number> tmp4;
  TNode<Number> tmp5;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_7);
    tmp4 = FromConstexpr_Number_constexpr_int31_0(state_, 1);
    tmp5 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{phi_bb6_7}, TNode<Number>{tmp4});
    ca_.Goto(&block3, tmp5);
  }

  TNode<Number> phi_bb2_7;
  TNode<Smi> tmp6;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_7);
    tmp6 = Convert_Smi_constexpr_int31_0(state_, -1);
    CodeStubAssembler(state_).Return(tmp6);
  }
}

TNode<Number> FastArrayFindIndex_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_o, TNode<Number> p_len, TNode<JSReceiver> p_callbackfn, TNode<Object> p_thisArg, compiler::CodeAssemblerLabel* label_Bailout, compiler::TypedCodeAssemblerVariable<Smi>* label_Bailout_parameter_0) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Object> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Object> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSArray> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<Smi> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    compiler::CodeAssemblerLabel label2(&ca_);
    tmp1 = Cast_Smi_0(state_, TNode<Object>{p_len}, &label2);
    ca_.Goto(&block5);
    if (label2.is_used()) {
      ca_.Bind(&label2);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block1, tmp0);
  }

  TNode<JSArray> tmp3;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    compiler::CodeAssemblerLabel label4(&ca_);
    tmp3 = Cast_FastJSArray_0(state_, TNode<Context>{p_context}, TNode<HeapObject>{p_o}, &label4);
    ca_.Goto(&block9);
    if (label4.is_used()) {
      ca_.Bind(&label4);
      ca_.Goto(&block10);
    }
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    ca_.Goto(&block1, tmp0);
  }

  TNode<JSArray> tmp5;
  TNode<JSArray> tmp6;
  TNode<Map> tmp7;
  TNode<BoolT> tmp8;
  TNode<BoolT> tmp9;
  TNode<BoolT> tmp10;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    std::tie(tmp5, tmp6, tmp7, tmp8, tmp9, tmp10) = NewFastJSArrayWitness_0(state_, TNode<JSArray>{tmp3}).Flatten();
    ca_.Goto(&block13, tmp0, tmp6);
  }

  TNode<Smi> phi_bb13_5;
  TNode<JSArray> phi_bb13_9;
  TNode<BoolT> tmp11;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_5, &phi_bb13_9);
    tmp11 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb13_5}, TNode<Smi>{tmp1});
    ca_.Branch(tmp11, &block11, std::vector<Node*>{phi_bb13_5, phi_bb13_9}, &block12, std::vector<Node*>{phi_bb13_5, phi_bb13_9});
  }

  TNode<Smi> phi_bb11_5;
  TNode<JSArray> phi_bb11_9;
  TNode<IntPtrT> tmp12;
  TNode<Map> tmp13;
  TNode<BoolT> tmp14;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_5, &phi_bb11_9);
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp13 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp5, tmp12});
    tmp14 = CodeStubAssembler(state_).TaggedNotEqual(TNode<HeapObject>{tmp13}, TNode<HeapObject>{tmp7});
    ca_.Branch(tmp14, &block18, std::vector<Node*>{phi_bb11_5, phi_bb11_9}, &block19, std::vector<Node*>{phi_bb11_5, phi_bb11_9});
  }

  TNode<Smi> phi_bb18_5;
  TNode<JSArray> phi_bb18_9;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_5, &phi_bb18_9);
    ca_.Goto(&block16, phi_bb18_5, phi_bb18_9);
  }

  TNode<Smi> phi_bb19_5;
  TNode<JSArray> phi_bb19_9;
  TNode<BoolT> tmp15;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_5, &phi_bb19_9);
    tmp15 = CodeStubAssembler(state_).IsNoElementsProtectorCellInvalid();
    ca_.Branch(tmp15, &block20, std::vector<Node*>{phi_bb19_5, phi_bb19_9}, &block21, std::vector<Node*>{phi_bb19_5, phi_bb19_9});
  }

  TNode<Smi> phi_bb20_5;
  TNode<JSArray> phi_bb20_9;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_5, &phi_bb20_9);
    ca_.Goto(&block16, phi_bb20_5, phi_bb20_9);
  }

  TNode<Smi> phi_bb21_5;
  TNode<JSArray> phi_bb21_9;
  TNode<JSArray> tmp16;
  TNode<Smi> tmp17;
  TNode<BoolT> tmp18;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_5, &phi_bb21_9);
    tmp16 = (TNode<JSArray>{tmp5});
    tmp17 = CodeStubAssembler(state_).LoadFastJSArrayLength(TNode<JSArray>{tmp16});
    tmp18 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{phi_bb21_5}, TNode<Smi>{tmp17});
    ca_.Branch(tmp18, &block22, std::vector<Node*>{phi_bb21_5}, &block23, std::vector<Node*>{phi_bb21_5});
  }

  TNode<Smi> phi_bb16_5;
  TNode<JSArray> phi_bb16_9;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_5, &phi_bb16_9);
    ca_.Goto(&block1, phi_bb16_5);
  }

  TNode<Smi> phi_bb22_5;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_5);
    ca_.Goto(&block1, phi_bb22_5);
  }

  TNode<Smi> phi_bb23_5;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_5);
    ca_.Branch(tmp8, &block29, std::vector<Node*>{phi_bb23_5, phi_bb23_5, phi_bb23_5, phi_bb23_5, phi_bb23_5}, &block30, std::vector<Node*>{phi_bb23_5, phi_bb23_5, phi_bb23_5, phi_bb23_5, phi_bb23_5});
  }

  TNode<Smi> phi_bb29_5;
  TNode<Smi> phi_bb29_14;
  TNode<Smi> phi_bb29_17;
  TNode<Smi> phi_bb29_18;
  TNode<Smi> phi_bb29_21;
  TNode<Object> tmp19;
  if (block29.is_used()) {
    ca_.Bind(&block29, &phi_bb29_5, &phi_bb29_14, &phi_bb29_17, &phi_bb29_18, &phi_bb29_21);
    compiler::CodeAssemblerLabel label20(&ca_);
    tmp19 = LoadElementNoHole_FixedDoubleArray_0(state_, TNode<Context>{p_context}, TNode<JSArray>{tmp16}, TNode<Smi>{phi_bb29_21}, &label20);
    ca_.Goto(&block32, phi_bb29_5, phi_bb29_14, phi_bb29_17, phi_bb29_18, phi_bb29_21, phi_bb29_21);
    if (label20.is_used()) {
      ca_.Bind(&label20);
      ca_.Goto(&block33, phi_bb29_5, phi_bb29_14, phi_bb29_17, phi_bb29_18, phi_bb29_21, phi_bb29_21);
    }
  }

  TNode<Smi> phi_bb33_5;
  TNode<Smi> phi_bb33_14;
  TNode<Smi> phi_bb33_17;
  TNode<Smi> phi_bb33_18;
  TNode<Smi> phi_bb33_21;
  TNode<Smi> phi_bb33_23;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_5, &phi_bb33_14, &phi_bb33_17, &phi_bb33_18, &phi_bb33_21, &phi_bb33_23);
    ca_.Goto(&block27, phi_bb33_5, phi_bb33_14, phi_bb33_17);
  }

  TNode<Smi> phi_bb32_5;
  TNode<Smi> phi_bb32_14;
  TNode<Smi> phi_bb32_17;
  TNode<Smi> phi_bb32_18;
  TNode<Smi> phi_bb32_21;
  TNode<Smi> phi_bb32_23;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_5, &phi_bb32_14, &phi_bb32_17, &phi_bb32_18, &phi_bb32_21, &phi_bb32_23);
    ca_.Goto(&block28, phi_bb32_5, phi_bb32_14, phi_bb32_17, phi_bb32_18, phi_bb32_21, tmp19);
  }

  TNode<Smi> phi_bb30_5;
  TNode<Smi> phi_bb30_14;
  TNode<Smi> phi_bb30_17;
  TNode<Smi> phi_bb30_18;
  TNode<Smi> phi_bb30_21;
  TNode<Object> tmp21;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_5, &phi_bb30_14, &phi_bb30_17, &phi_bb30_18, &phi_bb30_21);
    compiler::CodeAssemblerLabel label22(&ca_);
    tmp21 = LoadElementNoHole_FixedArray_0(state_, TNode<Context>{p_context}, TNode<JSArray>{tmp16}, TNode<Smi>{phi_bb30_21}, &label22);
    ca_.Goto(&block34, phi_bb30_5, phi_bb30_14, phi_bb30_17, phi_bb30_18, phi_bb30_21, phi_bb30_21);
    if (label22.is_used()) {
      ca_.Bind(&label22);
      ca_.Goto(&block35, phi_bb30_5, phi_bb30_14, phi_bb30_17, phi_bb30_18, phi_bb30_21, phi_bb30_21);
    }
  }

  TNode<Smi> phi_bb35_5;
  TNode<Smi> phi_bb35_14;
  TNode<Smi> phi_bb35_17;
  TNode<Smi> phi_bb35_18;
  TNode<Smi> phi_bb35_21;
  TNode<Smi> phi_bb35_23;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_5, &phi_bb35_14, &phi_bb35_17, &phi_bb35_18, &phi_bb35_21, &phi_bb35_23);
    ca_.Goto(&block27, phi_bb35_5, phi_bb35_14, phi_bb35_17);
  }

  TNode<Smi> phi_bb34_5;
  TNode<Smi> phi_bb34_14;
  TNode<Smi> phi_bb34_17;
  TNode<Smi> phi_bb34_18;
  TNode<Smi> phi_bb34_21;
  TNode<Smi> phi_bb34_23;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_5, &phi_bb34_14, &phi_bb34_17, &phi_bb34_18, &phi_bb34_21, &phi_bb34_23);
    ca_.Goto(&block28, phi_bb34_5, phi_bb34_14, phi_bb34_17, phi_bb34_18, phi_bb34_21, tmp21);
  }

  TNode<Smi> phi_bb28_5;
  TNode<Smi> phi_bb28_14;
  TNode<Smi> phi_bb28_17;
  TNode<Smi> phi_bb28_18;
  TNode<Smi> phi_bb28_21;
  TNode<Object> phi_bb28_22;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_5, &phi_bb28_14, &phi_bb28_17, &phi_bb28_18, &phi_bb28_21, &phi_bb28_22);
    ca_.Goto(&block25, phi_bb28_5, phi_bb28_14, phi_bb28_17, phi_bb28_22);
  }

  TNode<Smi> phi_bb27_5;
  TNode<Smi> phi_bb27_14;
  TNode<Smi> phi_bb27_17;
  TNode<Oddball> tmp23;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_5, &phi_bb27_14, &phi_bb27_17);
    tmp23 = Undefined_0(state_);
    ca_.Goto(&block25, phi_bb27_5, phi_bb27_14, phi_bb27_17, tmp23);
  }

  TNode<Smi> phi_bb25_5;
  TNode<Smi> phi_bb25_14;
  TNode<Smi> phi_bb25_17;
  TNode<Object> phi_bb25_18;
  TNode<Object> tmp24;
  TNode<BoolT> tmp25;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_5, &phi_bb25_14, &phi_bb25_17, &phi_bb25_18);
    tmp24 = CodeStubAssembler(state_).Call(TNode<Context>{p_context}, TNode<Object>{p_callbackfn}, TNode<Object>{p_thisArg}, TNode<Object>{phi_bb25_18}, TNode<Object>{phi_bb25_5}, TNode<Object>{tmp16});
    tmp25 = ToBoolean_0(state_, TNode<Object>{tmp24});
    ca_.Branch(tmp25, &block37, std::vector<Node*>{phi_bb25_5}, &block38, std::vector<Node*>{phi_bb25_5});
  }

  TNode<Smi> phi_bb37_5;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_5);
    ca_.Goto(&block2, phi_bb37_5);
  }

  TNode<Smi> phi_bb38_5;
  TNode<Smi> tmp26;
  TNode<Smi> tmp27;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_5);
    tmp26 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp27 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb38_5}, TNode<Smi>{tmp26});
    ca_.Goto(&block13, tmp27, tmp16);
  }

  TNode<Smi> phi_bb12_5;
  TNode<JSArray> phi_bb12_9;
  TNode<Number> tmp28;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_5, &phi_bb12_9);
    tmp28 = FromConstexpr_Number_constexpr_int31_0(state_, -1);
    ca_.Goto(&block2, tmp28);
  }

  TNode<Number> phi_bb2_5;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_5);
    ca_.Goto(&block39, phi_bb2_5);
  }

  TNode<Smi> phi_bb1_0;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_0);
    *label_Bailout_parameter_0 = phi_bb1_0;
    ca_.Goto(label_Bailout);
  }

  TNode<Number> phi_bb39_5;
    ca_.Bind(&block39, &phi_bb39_5);
  return TNode<Number>{phi_bb39_5};
}

TF_BUILTIN(ArrayPrototypeFindIndex, CodeStubAssembler) {
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
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    ca_.Goto(&block0);

  TNode<Object> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<Number> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<BoolT> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = RequireObjectCoercible_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, "Array.prototype.findIndex");
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
    compiler::TypedCodeAssemblerVariable<Smi> tmp13(&ca_);
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp10 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{tmp9});
    compiler::CodeAssemblerLabel label12(&ca_);
    tmp11 = FastArrayFindIndex_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp1}, TNode<Number>{tmp2}, TNode<JSReceiver>{tmp7}, TNode<Object>{tmp10}, &label12, &tmp13);
    ca_.Goto(&block9);
    if (label12.is_used()) {
      ca_.Bind(&label12);
      ca_.Goto(&block10);
    }
  }

  TNode<Number> tmp14;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp14 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kArrayFindIndexLoopContinuation, parameter0, tmp1, tmp7, tmp10, tmp1, tmp13.value(), tmp2));
    arguments.PopAndReturn(tmp14);
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    arguments.PopAndReturn(tmp11);
  }

  TNode<IntPtrT> tmp15;
  TNode<Object> tmp16;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp16 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{tmp15});
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, MessageTemplate::kCalledNonCallable, TNode<Object>{tmp16});
  }
}

TNode<Smi> Convert_Smi_constexpr_int31_0(compiler::CodeAssemblerState* state_, int31_t p_i) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_int31_0(state_, p_i);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Smi>{tmp0};
}

}  // namespace internal
}  // namespace v8

