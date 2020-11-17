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

const char* kBuiltinNameFrom_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  return "%TypedArray%.from";
}

TF_BUILTIN(TypedArrayFrom, CodeStubAssembler) {
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
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, Object> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, Object> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, Object> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, Object> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, Object> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, Object> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, Object> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, Object> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, Object, UintPtrT> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, Object, UintPtrT> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, Object, UintPtrT> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, Object, UintPtrT> block48(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, Object, UintPtrT, Object> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, Object, UintPtrT, UintPtrT, UintPtrT> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, Object, UintPtrT, UintPtrT, UintPtrT> block52(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, Object, UintPtrT> block44(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Object> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Object> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<Object> tmp5;
  TNode<JSReceiver> tmp6;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp1 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{tmp0});
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp3 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{tmp2});
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 2);
    tmp5 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{tmp4});
    compiler::CodeAssemblerLabel label7(&ca_);
    tmp6 = Cast_Constructor_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label7);
    ca_.Goto(&block5);
    if (label7.is_used()) {
      ca_.Bind(&label7);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, MessageTemplate::kNotConstructor, TNode<Object>{parameter1});
  }

  TNode<Oddball> tmp8;
  TNode<BoolT> tmp9;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp8 = Undefined_0(state_);
    tmp9 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{tmp3}, TNode<HeapObject>{tmp8});
    ca_.Branch(tmp9, &block9, std::vector<Node*>{}, &block10, std::vector<Node*>{});
  }

  TNode<BoolT> tmp10;
  TNode<BoolT> tmp11;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp10 = Is_Callable_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp3});
    tmp11 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp10});
    ca_.Goto(&block11, tmp11);
  }

  TNode<BoolT> tmp12;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp12 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block11, tmp12);
  }

  TNode<BoolT> phi_bb11_11;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_11);
    ca_.Branch(phi_bb11_11, &block7, std::vector<Node*>{}, &block8, std::vector<Node*>{});
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, MessageTemplate::kCalledNonCallable, TNode<Object>{tmp3});
  }

  TNode<Symbol> tmp13;
  TNode<JSReceiver> tmp14;
    compiler::TypedCodeAssemblerVariable<Object> tmp17(&ca_);
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp13 = CodeStubAssembler(state_).IteratorSymbolConstant();
    compiler::CodeAssemblerLabel label15(&ca_);
    compiler::CodeAssemblerLabel label16(&ca_);
    tmp14 = GetMethod_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1}, TNode<Name>{tmp13}, &label15, &label16, &tmp17);
    ca_.Goto(&block16);
    if (label15.is_used()) {
      ca_.Bind(&label15);
      ca_.Goto(&block17);
    }
    if (label16.is_used()) {
      ca_.Bind(&label16);
      ca_.Goto(&block18);
    }
  }

  TNode<JSReceiver> tmp18;
  TNode<Number> tmp19;
  TNode<UintPtrT> tmp20;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp18 = CodeStubAssembler(state_).ToObject_Inline(TNode<Context>{parameter0}, TNode<Object>{tmp1});
    tmp19 = GetLengthProperty_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp18});
    compiler::CodeAssemblerLabel label21(&ca_);
    tmp20 = ChangeSafeIntegerNumberToUintPtr_0(state_, TNode<Number>{tmp19}, &label21);
    ca_.Goto(&block33);
    if (label21.is_used()) {
      ca_.Bind(&label21);
      ca_.Goto(&block34);
    }
  }

  if (block18.is_used()) {
    ca_.Bind(&block18);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, MessageTemplate::kIteratorSymbolNonCallable);
  }

  TNode<JSTypedArray> tmp22;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    compiler::CodeAssemblerLabel label23(&ca_);
    tmp22 = Cast_JSTypedArray_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1}, &label23);
    ca_.Goto(&block21);
    if (label23.is_used()) {
      ca_.Bind(&label23);
      ca_.Goto(&block22);
    }
  }

  if (block22.is_used()) {
    ca_.Bind(&block22);
    ca_.Goto(&block20);
  }

  TNode<IntPtrT> tmp24;
  TNode<JSArrayBuffer> tmp25;
  TNode<BoolT> tmp26;
  if (block21.is_used()) {
    ca_.Bind(&block21);
    tmp24 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp25 = CodeStubAssembler(state_).LoadReference<JSArrayBuffer>(CodeStubAssembler::Reference{tmp22, tmp24});
    tmp26 = IsDetachedBuffer_0(state_, TNode<JSArrayBuffer>{tmp25});
    ca_.Branch(tmp26, &block23, std::vector<Node*>{}, &block24, std::vector<Node*>{});
  }

  if (block23.is_used()) {
    ca_.Bind(&block23);
    ca_.Goto(&block20);
  }

  TNode<JSFunction> tmp27;
  if (block24.is_used()) {
    ca_.Bind(&block24);
    compiler::CodeAssemblerLabel label28(&ca_);
    tmp27 = Cast_JSFunction_0(state_, TNode<HeapObject>{tmp14}, &label28);
    ca_.Goto(&block25);
    if (label28.is_used()) {
      ca_.Bind(&label28);
      ca_.Goto(&block26);
    }
  }

  if (block26.is_used()) {
    ca_.Bind(&block26);
    ca_.Goto(&block20);
  }

  TNode<IntPtrT> tmp29;
  TNode<SharedFunctionInfo> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<Object> tmp32;
  TNode<Smi> tmp33;
  TNode<BoolT> tmp34;
  TNode<BoolT> tmp35;
  if (block25.is_used()) {
    ca_.Bind(&block25);
    tmp29 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp30 = CodeStubAssembler(state_).LoadReference<SharedFunctionInfo>(CodeStubAssembler::Reference{tmp27, tmp29});
    tmp31 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp32 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp30, tmp31});
    tmp33 = CodeStubAssembler(state_).SmiConstant(Builtins::kTypedArrayPrototypeValues);
    tmp34 = CodeStubAssembler(state_).TaggedEqual(TNode<MaybeObject>{tmp32}, TNode<MaybeObject>{tmp33});
    tmp35 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp34});
    ca_.Branch(tmp35, &block27, std::vector<Node*>{}, &block28, std::vector<Node*>{});
  }

  if (block27.is_used()) {
    ca_.Bind(&block27);
    ca_.Goto(&block20);
  }

  TNode<BoolT> tmp36;
  if (block28.is_used()) {
    ca_.Bind(&block28);
    tmp36 = CodeStubAssembler(state_).IsArrayIteratorProtectorCellInvalid();
    ca_.Branch(tmp36, &block29, std::vector<Node*>{}, &block30, std::vector<Node*>{});
  }

  if (block29.is_used()) {
    ca_.Bind(&block29);
    ca_.Goto(&block20);
  }

  TNode<IntPtrT> tmp37;
  TNode<UintPtrT> tmp38;
  if (block30.is_used()) {
    ca_.Bind(&block30);
    tmp37 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp38 = CodeStubAssembler(state_).LoadReference<UintPtrT>(CodeStubAssembler::Reference{tmp22, tmp37});
    ca_.Goto(&block19, tmp38, tmp1);
  }

  TNode<JSArray> tmp39;
  TNode<IntPtrT> tmp40;
  TNode<Number> tmp41;
  TNode<UintPtrT> tmp42;
  if (block20.is_used()) {
    ca_.Bind(&block20);
    tmp39 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kIterableToList, parameter0, tmp1, tmp14));
    tmp40 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp41 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{tmp39, tmp40});
    tmp42 = Convert_uintptr_Number_0(state_, TNode<Number>{tmp41});
    ca_.Goto(&block19, tmp42, tmp39);
  }

  TNode<UintPtrT> phi_bb19_10;
  TNode<Object> phi_bb19_11;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_10, &phi_bb19_11);
    ca_.Goto(&block14, phi_bb19_10, phi_bb19_11);
  }

  if (block34.is_used()) {
    ca_.Bind(&block34);
    CodeStubAssembler(state_).ThrowRangeError(TNode<Context>{parameter0}, MessageTemplate::kInvalidTypedArrayLength, TNode<Object>{tmp19});
  }

  if (block33.is_used()) {
    ca_.Bind(&block33);
    ca_.Goto(&block14, tmp20, tmp18);
  }

  TNode<UintPtrT> phi_bb14_10;
  TNode<Object> phi_bb14_11;
  TNode<Number> tmp43;
  TNode<JSTypedArray> tmp44;
  TNode<BoolT> tmp45;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_10, &phi_bb14_11);
    tmp43 = Convert_Number_uintptr_0(state_, TNode<UintPtrT>{phi_bb14_10});
    tmp44 = TypedArrayCreateByLength_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp6}, TNode<Number>{tmp43}, kBuiltinNameFrom_0(state_));
    tmp45 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp9});
    ca_.Branch(tmp45, &block35, std::vector<Node*>{phi_bb14_10, phi_bb14_11}, &block36, std::vector<Node*>{phi_bb14_10, phi_bb14_11});
  }

  TNode<UintPtrT> phi_bb35_10;
  TNode<Object> phi_bb35_11;
  TNode<UintPtrT> tmp46;
  TNode<BoolT> tmp47;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_10, &phi_bb35_11);
    tmp46 = FromConstexpr_uintptr_constexpr_int31_0(state_, 0);
    tmp47 = CodeStubAssembler(state_).WordNotEqual(TNode<UintPtrT>{phi_bb35_10}, TNode<UintPtrT>{tmp46});
    ca_.Branch(tmp47, &block37, std::vector<Node*>{phi_bb35_10, phi_bb35_11}, &block38, std::vector<Node*>{phi_bb35_10, phi_bb35_11});
  }

  TNode<UintPtrT> phi_bb37_10;
  TNode<Object> phi_bb37_11;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_10, &phi_bb37_11);
    CodeStubAssembler(state_).CallRuntime(Runtime::kTypedArrayCopyElements, parameter0, tmp44, phi_bb37_11, tmp43);
    ca_.Goto(&block38, phi_bb37_10, phi_bb37_11);
  }

  TNode<UintPtrT> phi_bb38_10;
  TNode<Object> phi_bb38_11;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_10, &phi_bb38_11);
    arguments.PopAndReturn(tmp44);
  }

  TNode<UintPtrT> phi_bb36_10;
  TNode<Object> phi_bb36_11;
  TNode<JSReceiver> tmp48;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_10, &phi_bb36_11);
    compiler::CodeAssemblerLabel label49(&ca_);
    tmp48 = Cast_Callable_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp3}, &label49);
    ca_.Goto(&block41, phi_bb36_10, phi_bb36_11);
    if (label49.is_used()) {
      ca_.Bind(&label49);
      ca_.Goto(&block42, phi_bb36_10, phi_bb36_11);
    }
  }

  TNode<UintPtrT> phi_bb42_10;
  TNode<Object> phi_bb42_11;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_10, &phi_bb42_11);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<UintPtrT> phi_bb41_10;
  TNode<Object> phi_bb41_11;
  TNode<Int32T> tmp50;
  TNode<BuiltinPtr> tmp51;
  TNode<BuiltinPtr> tmp52;
  TNode<BuiltinPtr> tmp53;
  TNode<UintPtrT> tmp54;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_10, &phi_bb41_11);
    tmp50 = CodeStubAssembler(state_).LoadElementsKind(TNode<JSTypedArray>{tmp44});
    std::tie(tmp51, tmp52, tmp53) = GetTypedArrayAccessor_0(state_, TNode<Int32T>{tmp50}).Flatten();
    tmp54 = FromConstexpr_uintptr_constexpr_int31_0(state_, 0);
    ca_.Goto(&block45, phi_bb41_10, phi_bb41_11, tmp54);
  }

  TNode<UintPtrT> phi_bb45_10;
  TNode<Object> phi_bb45_11;
  TNode<UintPtrT> phi_bb45_18;
  TNode<BoolT> tmp55;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_10, &phi_bb45_11, &phi_bb45_18);
    tmp55 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{phi_bb45_18}, TNode<UintPtrT>{phi_bb45_10});
    ca_.Branch(tmp55, &block43, std::vector<Node*>{phi_bb45_10, phi_bb45_11, phi_bb45_18}, &block44, std::vector<Node*>{phi_bb45_10, phi_bb45_11, phi_bb45_18});
  }

  TNode<UintPtrT> phi_bb43_10;
  TNode<Object> phi_bb43_11;
  TNode<UintPtrT> phi_bb43_18;
  TNode<Number> tmp56;
  TNode<Object> tmp57;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_10, &phi_bb43_11, &phi_bb43_18);
    tmp56 = Convert_Number_uintptr_0(state_, TNode<UintPtrT>{phi_bb43_18});
    tmp57 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<Object>{phi_bb43_11}, TNode<Object>{tmp56});
    ca_.Branch(tmp9, &block47, std::vector<Node*>{phi_bb43_10, phi_bb43_11, phi_bb43_18}, &block48, std::vector<Node*>{phi_bb43_10, phi_bb43_11, phi_bb43_18});
  }

  TNode<UintPtrT> phi_bb47_10;
  TNode<Object> phi_bb47_11;
  TNode<UintPtrT> phi_bb47_18;
  TNode<Object> tmp58;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_10, &phi_bb47_11, &phi_bb47_18);
    tmp58 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<Object>{tmp48}, TNode<Object>{tmp5}, TNode<Object>{tmp57}, TNode<Object>{tmp56});
    ca_.Goto(&block49, phi_bb47_10, phi_bb47_11, phi_bb47_18, tmp58);
  }

  TNode<UintPtrT> phi_bb48_10;
  TNode<Object> phi_bb48_11;
  TNode<UintPtrT> phi_bb48_18;
  if (block48.is_used()) {
    ca_.Bind(&block48, &phi_bb48_10, &phi_bb48_11, &phi_bb48_18);
    ca_.Goto(&block49, phi_bb48_10, phi_bb48_11, phi_bb48_18, tmp57);
  }

  TNode<UintPtrT> phi_bb49_10;
  TNode<Object> phi_bb49_11;
  TNode<UintPtrT> phi_bb49_18;
  TNode<Object> phi_bb49_21;
  TNode<Smi> tmp59;
  TNode<Smi> tmp60;
  TNode<BoolT> tmp61;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_10, &phi_bb49_11, &phi_bb49_18, &phi_bb49_21);
tmp59 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltinPointer(Builtins::CallableFor(ca_.isolate(),ExampleBuiltinForTorqueFunctionPointerType(3)).descriptor(), tmp53, parameter0, tmp44, phi_bb49_18, phi_bb49_21));
    tmp60 = kStoreFailureArrayDetached_0(state_);
    tmp61 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp59}, TNode<Smi>{tmp60});
    ca_.Branch(tmp61, &block51, std::vector<Node*>{phi_bb49_10, phi_bb49_11, phi_bb49_18, phi_bb49_18, phi_bb49_18}, &block52, std::vector<Node*>{phi_bb49_10, phi_bb49_11, phi_bb49_18, phi_bb49_18, phi_bb49_18});
  }

  TNode<UintPtrT> phi_bb51_10;
  TNode<Object> phi_bb51_11;
  TNode<UintPtrT> phi_bb51_18;
  TNode<UintPtrT> phi_bb51_27;
  TNode<UintPtrT> phi_bb51_31;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_10, &phi_bb51_11, &phi_bb51_18, &phi_bb51_27, &phi_bb51_31);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, MessageTemplate::kDetachedOperation, kBuiltinNameFrom_0(state_));
  }

  TNode<UintPtrT> phi_bb52_10;
  TNode<Object> phi_bb52_11;
  TNode<UintPtrT> phi_bb52_18;
  TNode<UintPtrT> phi_bb52_27;
  TNode<UintPtrT> phi_bb52_31;
  TNode<UintPtrT> tmp62;
  TNode<UintPtrT> tmp63;
  if (block52.is_used()) {
    ca_.Bind(&block52, &phi_bb52_10, &phi_bb52_11, &phi_bb52_18, &phi_bb52_27, &phi_bb52_31);
    tmp62 = FromConstexpr_uintptr_constexpr_int31_0(state_, 1);
    tmp63 = CodeStubAssembler(state_).UintPtrAdd(TNode<UintPtrT>{phi_bb52_18}, TNode<UintPtrT>{tmp62});
    ca_.Goto(&block45, phi_bb52_10, phi_bb52_11, tmp63);
  }

  TNode<UintPtrT> phi_bb44_10;
  TNode<Object> phi_bb44_11;
  TNode<UintPtrT> phi_bb44_18;
  if (block44.is_used()) {
    ca_.Bind(&block44, &phi_bb44_10, &phi_bb44_11, &phi_bb44_18);
    arguments.PopAndReturn(tmp44);
  }
}

}  // namespace internal
}  // namespace v8

