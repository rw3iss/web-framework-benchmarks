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

TF_BUILTIN(ArrayFrom, CodeStubAssembler) {
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
  compiler::CodeAssemblerParameterizedLabel<BoolT> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, JSReceiver> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block42(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi, Smi> block43(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi, Object> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi, Object> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi, Smi> block46(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block50(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, JSReceiver> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block53(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block54(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block55(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi, Object> block56(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block52(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp1 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{tmp0});
    ca_.Branch(tmp1, &block3, std::vector<Node*>{}, &block4, std::vector<Node*>{});
  }

  TNode<JSFunction> tmp2;
  TNode<BoolT> tmp3;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = GetArrayFunction_0(state_, TNode<Context>{parameter0});
    tmp3 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{parameter1}, TNode<HeapObject>{tmp2});
    ca_.Goto(&block5, tmp3);
  }

  TNode<BoolT> tmp4;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp4 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block5, tmp4);
  }

  TNode<BoolT> phi_bb5_6;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_6);
    ca_.Branch(phi_bb5_6, &block1, std::vector<Node*>{}, &block2, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp5;
  TNode<Object> tmp6;
  TNode<JSArray> tmp7;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp5 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp6 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{tmp5});
    compiler::CodeAssemblerLabel label8(&ca_);
    tmp7 = IteratorBuiltinsAssembler(state_).FastIterableToList(TNode<Context>{parameter0}, TNode<Object>{tmp6}, &label8);
    ca_.Goto(&block8);
    if (label8.is_used()) {
      ca_.Bind(&label8);
      ca_.Goto(&block9);
    }
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    ca_.Goto(&block2);
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    arguments.PopAndReturn(tmp7);
  }

  TNode<IntPtrT> tmp9;
  TNode<Object> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<Object> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<Object> tmp14;
  TNode<Oddball> tmp15;
  TNode<BoolT> tmp16;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp10 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{tmp9});
    tmp11 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp12 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{tmp11});
    tmp13 = FromConstexpr_intptr_constexpr_int31_0(state_, 2);
    tmp14 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{tmp13});
    tmp15 = Undefined_0(state_);
    tmp16 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp12}, TNode<HeapObject>{tmp15});
    ca_.Branch(tmp16, &block10, std::vector<Node*>{}, &block11, std::vector<Node*>{});
  }

  TNode<BoolT> tmp17;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp17 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block12, tmp17);
  }

  TNode<BoolT> tmp18;
  TNode<BoolT> tmp19;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp18 = Is_Callable_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp12});
    tmp19 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp18});
    ca_.Branch(tmp19, &block13, std::vector<Node*>{}, &block14, std::vector<Node*>{});
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, MessageTemplate::kCalledNonCallable, TNode<Object>{tmp12});
  }

  TNode<BoolT> tmp20;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp20 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block12, tmp20);
  }

  TNode<BoolT> phi_bb12_9;
  TNode<Symbol> tmp21;
  TNode<JSReceiver> tmp22;
    compiler::TypedCodeAssemblerVariable<Object> tmp25(&ca_);
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_9);
    tmp21 = CodeStubAssembler(state_).IteratorSymbolConstant();
    compiler::CodeAssemblerLabel label23(&ca_);
    compiler::CodeAssemblerLabel label24(&ca_);
    tmp22 = GetMethod_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp10}, TNode<Name>{tmp21}, &label23, &label24, &tmp25);
    ca_.Goto(&block19, phi_bb12_9);
    if (label23.is_used()) {
      ca_.Bind(&label23);
      ca_.Goto(&block20, phi_bb12_9);
    }
    if (label24.is_used()) {
      ca_.Bind(&label24);
      ca_.Goto(&block21, phi_bb12_9);
    }
  }

  TNode<BoolT> phi_bb20_9;
  TNode<JSReceiver> tmp26;
  TNode<Number> tmp27;
  TNode<JSReceiver> tmp28;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_9);
    tmp26 = CodeStubAssembler(state_).ToObject_Inline(TNode<Context>{parameter0}, TNode<Object>{tmp10});
    tmp27 = GetLengthProperty_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp26});
    compiler::CodeAssemblerLabel label29(&ca_);
    tmp28 = Cast_Constructor_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label29);
    ca_.Goto(&block49, phi_bb20_9);
    if (label29.is_used()) {
      ca_.Bind(&label29);
      ca_.Goto(&block50, phi_bb20_9);
    }
  }

  TNode<BoolT> phi_bb21_9;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_9);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, MessageTemplate::kIteratorSymbolNonCallable);
  }

  TNode<BoolT> phi_bb19_9;
  TNode<JSReceiver> tmp30;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_9);
    compiler::CodeAssemblerLabel label31(&ca_);
    tmp30 = Cast_Constructor_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label31);
    ca_.Goto(&block24, phi_bb19_9);
    if (label31.is_used()) {
      ca_.Bind(&label31);
      ca_.Goto(&block25, phi_bb19_9);
    }
  }

  TNode<BoolT> phi_bb25_9;
  TNode<Number> tmp32;
  TNode<JSArray> tmp33;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_9);
    tmp32 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp33 = CodeStubAssembler(state_).ArrayCreate(TNode<Context>{parameter0}, TNode<Number>{tmp32});
    ca_.Goto(&block22, phi_bb25_9, tmp33);
  }

  TNode<BoolT> phi_bb24_9;
  TNode<JSReceiver> tmp34;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_9);
    tmp34 = CodeStubAssembler(state_).Construct(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp30});
    ca_.Goto(&block22, phi_bb24_9, tmp34);
  }

  TNode<BoolT> phi_bb22_9;
  TNode<JSReceiver> phi_bb22_11;
  TNode<JSReceiver> tmp35;
  TNode<Object> tmp36;
  TNode<Map> tmp37;
  TNode<Smi> tmp38;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_9, &phi_bb22_11);
    std::tie(tmp35, tmp36) = IteratorBuiltinsAssembler(state_).GetIterator(TNode<Context>{parameter0}, TNode<Object>{tmp10}, TNode<Object>{tmp22}).Flatten();
    tmp37 = GetIteratorResultMap_0(state_, TNode<Context>{parameter0});
    tmp38 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    ca_.Goto(&block28, phi_bb22_9, tmp38);
  }

  TNode<BoolT> phi_bb28_9;
  TNode<Smi> phi_bb28_15;
  TNode<BoolT> tmp39;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_9, &phi_bb28_15);
    tmp39 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Branch(tmp39, &block26, std::vector<Node*>{phi_bb28_9, phi_bb28_15}, &block27, std::vector<Node*>{phi_bb28_9, phi_bb28_15});
  }

  TNode<BoolT> phi_bb26_9;
  TNode<Smi> phi_bb26_15;
  TNode<JSReceiver> tmp40;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_9, &phi_bb26_15);
    compiler::CodeAssemblerLabel label41(&ca_);
    tmp40 = IteratorBuiltinsAssembler(state_).IteratorStep(TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp35}, TNode<Object>{tmp36}}, TNode<Map>{tmp37}, &label41);
    ca_.Goto(&block35, phi_bb26_9, phi_bb26_15);
    if (label41.is_used()) {
      ca_.Bind(&label41);
      ca_.Goto(&block36, phi_bb26_9, phi_bb26_15);
    }
  }

  TNode<BoolT> phi_bb36_9;
  TNode<Smi> phi_bb36_15;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_9, &phi_bb36_15);
    CodeStubAssembler(state_).SetPropertyLength(TNode<Context>{parameter0}, TNode<Object>{phi_bb22_11}, TNode<Number>{phi_bb36_15});
    arguments.PopAndReturn(phi_bb22_11);
  }

  TNode<BoolT> phi_bb35_9;
  TNode<Smi> phi_bb35_15;
  TNode<Object> tmp42;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_9, &phi_bb35_15);
    tmp42 = IteratorBuiltinsAssembler(state_).IteratorValue(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp40}, TNode<Map>{tmp37});
    ca_.Branch(phi_bb35_9, &block37, std::vector<Node*>{phi_bb35_9, phi_bb35_15}, &block38, std::vector<Node*>{phi_bb35_9, phi_bb35_15});
  }

  TNode<BoolT> phi_bb37_9;
  TNode<Smi> phi_bb37_15;
  TNode<JSReceiver> tmp43;
      TNode<Object> tmp45;
  TNode<Object> tmp46;
      TNode<Object> tmp48;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_9, &phi_bb37_15);
    compiler::CodeAssemblerExceptionHandlerLabel catch44__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch44__label);
    tmp43 = UnsafeCast_Callable_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp12});
    }
    if (catch44__label.is_used()) {
      compiler::CodeAssemblerLabel catch44_skip(&ca_);
      ca_.Goto(&catch44_skip);
      ca_.Bind(&catch44__label, &tmp45);
      ca_.Goto(&block42, phi_bb37_9, phi_bb37_15);
      ca_.Bind(&catch44_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch47__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch47__label);
    tmp46 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<Object>{tmp43}, TNode<Object>{tmp14}, TNode<Object>{tmp42}, TNode<Object>{phi_bb37_15});
    }
    if (catch47__label.is_used()) {
      compiler::CodeAssemblerLabel catch47_skip(&ca_);
      ca_.Goto(&catch47_skip);
      ca_.Bind(&catch47__label, &tmp48);
      ca_.Goto(&block43, phi_bb37_9, phi_bb37_15, phi_bb37_15);
      ca_.Bind(&catch47_skip);
    }
    ca_.Goto(&block39, phi_bb37_9, phi_bb37_15, tmp46);
  }

  TNode<BoolT> phi_bb42_9;
  TNode<Smi> phi_bb42_15;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_9, &phi_bb42_15);
    ca_.Goto(&block41, phi_bb42_9, phi_bb42_15, tmp45);
  }

  TNode<BoolT> phi_bb43_9;
  TNode<Smi> phi_bb43_15;
  TNode<Smi> phi_bb43_23;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_9, &phi_bb43_15, &phi_bb43_23);
    ca_.Goto(&block41, phi_bb43_9, phi_bb43_15, tmp48);
  }

  TNode<BoolT> phi_bb41_9;
  TNode<Smi> phi_bb41_15;
  TNode<Object> phi_bb41_19;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_9, &phi_bb41_15, &phi_bb41_19);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp35}, TNode<Object>{tmp36}});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrow, parameter0, phi_bb41_19);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> phi_bb38_9;
  TNode<Smi> phi_bb38_15;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_9, &phi_bb38_15);
    ca_.Goto(&block39, phi_bb38_9, phi_bb38_15, tmp42);
  }

  TNode<BoolT> phi_bb39_9;
  TNode<Smi> phi_bb39_15;
  TNode<Object> phi_bb39_18;
  TNode<Object> tmp49;
      TNode<Object> tmp51;
  TNode<Smi> tmp52;
  TNode<Smi> tmp53;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_9, &phi_bb39_15, &phi_bb39_18);
    compiler::CodeAssemblerExceptionHandlerLabel catch50__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch50__label);
    tmp49 = CodeStubAssembler(state_).CallBuiltin(Builtins::kFastCreateDataProperty, parameter0, phi_bb22_11, phi_bb39_15, phi_bb39_18);
    }
    if (catch50__label.is_used()) {
      compiler::CodeAssemblerLabel catch50_skip(&ca_);
      ca_.Goto(&catch50_skip);
      ca_.Bind(&catch50__label, &tmp51);
      ca_.Goto(&block46, phi_bb39_9, phi_bb39_15, phi_bb39_15);
      ca_.Bind(&catch50_skip);
    }
    tmp52 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp53 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb39_15}, TNode<Smi>{tmp52});
    ca_.Goto(&block28, phi_bb39_9, tmp53);
  }

  TNode<BoolT> phi_bb46_9;
  TNode<Smi> phi_bb46_15;
  TNode<Smi> phi_bb46_20;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_9, &phi_bb46_15, &phi_bb46_20);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp35}, TNode<Object>{tmp36}});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrow, parameter0, tmp51);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> phi_bb27_9;
  TNode<Smi> phi_bb27_15;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_9, &phi_bb27_15);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> phi_bb50_9;
  TNode<JSArray> tmp54;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_9);
    tmp54 = CodeStubAssembler(state_).ArrayCreate(TNode<Context>{parameter0}, TNode<Number>{tmp27});
    ca_.Goto(&block47, phi_bb50_9, tmp54);
  }

  TNode<BoolT> phi_bb49_9;
  TNode<JSReceiver> tmp55;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_9);
    tmp55 = CodeStubAssembler(state_).Construct(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp28}, TNode<Object>{tmp27});
    ca_.Goto(&block47, phi_bb49_9, tmp55);
  }

  TNode<BoolT> phi_bb47_9;
  TNode<JSReceiver> phi_bb47_12;
  TNode<Smi> tmp56;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_9, &phi_bb47_12);
    tmp56 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    ca_.Goto(&block53, phi_bb47_9, tmp56);
  }

  TNode<BoolT> phi_bb53_9;
  TNode<Smi> phi_bb53_13;
  TNode<BoolT> tmp57;
  if (block53.is_used()) {
    ca_.Bind(&block53, &phi_bb53_9, &phi_bb53_13);
    tmp57 = NumberIsLessThan_0(state_, TNode<Number>{phi_bb53_13}, TNode<Number>{tmp27});
    ca_.Branch(tmp57, &block51, std::vector<Node*>{phi_bb53_9, phi_bb53_13}, &block52, std::vector<Node*>{phi_bb53_9, phi_bb53_13});
  }

  TNode<BoolT> phi_bb51_9;
  TNode<Smi> phi_bb51_13;
  TNode<Object> tmp58;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_9, &phi_bb51_13);
    tmp58 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<Object>{tmp26}, TNode<Object>{phi_bb51_13});
    ca_.Branch(phi_bb51_9, &block54, std::vector<Node*>{phi_bb51_9, phi_bb51_13}, &block55, std::vector<Node*>{phi_bb51_9, phi_bb51_13});
  }

  TNode<BoolT> phi_bb54_9;
  TNode<Smi> phi_bb54_13;
  TNode<JSReceiver> tmp59;
  TNode<Object> tmp60;
  if (block54.is_used()) {
    ca_.Bind(&block54, &phi_bb54_9, &phi_bb54_13);
    tmp59 = UnsafeCast_Callable_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp12});
    tmp60 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<Object>{tmp59}, TNode<Object>{tmp14}, TNode<Object>{tmp58}, TNode<Object>{phi_bb54_13});
    ca_.Goto(&block56, phi_bb54_9, phi_bb54_13, tmp60);
  }

  TNode<BoolT> phi_bb55_9;
  TNode<Smi> phi_bb55_13;
  if (block55.is_used()) {
    ca_.Bind(&block55, &phi_bb55_9, &phi_bb55_13);
    ca_.Goto(&block56, phi_bb55_9, phi_bb55_13, tmp58);
  }

  TNode<BoolT> phi_bb56_9;
  TNode<Smi> phi_bb56_13;
  TNode<Object> phi_bb56_15;
  TNode<Object> tmp61;
  TNode<Smi> tmp62;
  TNode<Smi> tmp63;
  if (block56.is_used()) {
    ca_.Bind(&block56, &phi_bb56_9, &phi_bb56_13, &phi_bb56_15);
    tmp61 = CodeStubAssembler(state_).CallBuiltin(Builtins::kFastCreateDataProperty, parameter0, phi_bb47_12, phi_bb56_13, phi_bb56_15);
    tmp62 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp63 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb56_13}, TNode<Smi>{tmp62});
    ca_.Goto(&block53, phi_bb56_9, tmp63);
  }

  TNode<BoolT> phi_bb52_9;
  TNode<Smi> phi_bb52_13;
  if (block52.is_used()) {
    ca_.Bind(&block52, &phi_bb52_9, &phi_bb52_13);
    CodeStubAssembler(state_).SetPropertyLength(TNode<Context>{parameter0}, TNode<Object>{phi_bb47_12}, TNode<Number>{tmp27});
    arguments.PopAndReturn(phi_bb47_12);
  }
}

TNode<BoolT> Is_Callable_JSAny_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_Callable_1(state_, TNode<Context>{p_context}, TNode<Object>{p_o}, &label1);
    ca_.Goto(&block4);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block5);
    }
  }

  TNode<BoolT> tmp2;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp2 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block1, tmp2);
  }

  TNode<BoolT> tmp3;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp3 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block1, tmp3);
  }

  TNode<BoolT> phi_bb1_2;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_2);
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
  return TNode<BoolT>{phi_bb1_2};
}

TNode<JSReceiver> Cast_Constructor_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError) {
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

  TNode<JSReceiver> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_Constructor_0(state_, TNode<HeapObject>{tmp0}, &label3);
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
  return TNode<JSReceiver>{tmp2};
}

TNode<JSReceiver> UnsafeCast_Callable_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
  return TNode<JSReceiver>{tmp0};
}

}  // namespace internal
}  // namespace v8

