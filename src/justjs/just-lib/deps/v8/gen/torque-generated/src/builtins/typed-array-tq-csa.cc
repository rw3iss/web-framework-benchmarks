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

TNode<Smi> kStoreSucceded_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  TNode<Smi> tmp0;
    tmp0 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
  return TNode<Smi>{tmp0};
}

TNode<Smi> kStoreFailureArrayDetached_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  TNode<Smi> tmp0;
    tmp0 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
  return TNode<Smi>{tmp0};
}

TorqueStructTypedArrayAccessor_0 GetTypedArrayAccessor_0(compiler::CodeAssemblerState* state_, TNode<Int32T> p_elementsKind) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, BuiltinPtr, BuiltinPtr> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).IsElementsKindGreaterThan(TNode<Int32T>{p_elementsKind}, ElementsKind::UINT32_ELEMENTS);
    ca_.Branch(tmp0, &block2, std::vector<Node*>{}, &block3, std::vector<Node*>{});
  }

  TNode<Int32T> tmp1;
  TNode<BoolT> tmp2;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = FromConstexpr_ElementsKind_constexpr_INT32_ELEMENTS_0(state_, ElementsKind::INT32_ELEMENTS);
    tmp2 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{p_elementsKind}, TNode<Int32T>{tmp1});
    ca_.Branch(tmp2, &block5, std::vector<Node*>{}, &block6, std::vector<Node*>{});
  }

  TNode<BuiltinPtr> tmp3;
  TNode<BuiltinPtr> tmp4;
  TNode<BuiltinPtr> tmp5;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    std::tie(tmp3, tmp4, tmp5) = GetTypedArrayAccessor_Int32Elements_0(state_).Flatten();
    ca_.Goto(&block1, tmp3, tmp4, tmp5);
  }

  TNode<Int32T> tmp6;
  TNode<BoolT> tmp7;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp6 = FromConstexpr_ElementsKind_constexpr_FLOAT32_ELEMENTS_0(state_, ElementsKind::FLOAT32_ELEMENTS);
    tmp7 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{p_elementsKind}, TNode<Int32T>{tmp6});
    ca_.Branch(tmp7, &block8, std::vector<Node*>{}, &block9, std::vector<Node*>{});
  }

  TNode<BuiltinPtr> tmp8;
  TNode<BuiltinPtr> tmp9;
  TNode<BuiltinPtr> tmp10;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    std::tie(tmp8, tmp9, tmp10) = GetTypedArrayAccessor_Float32Elements_0(state_).Flatten();
    ca_.Goto(&block1, tmp8, tmp9, tmp10);
  }

  TNode<Int32T> tmp11;
  TNode<BoolT> tmp12;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp11 = FromConstexpr_ElementsKind_constexpr_FLOAT64_ELEMENTS_0(state_, ElementsKind::FLOAT64_ELEMENTS);
    tmp12 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{p_elementsKind}, TNode<Int32T>{tmp11});
    ca_.Branch(tmp12, &block11, std::vector<Node*>{}, &block12, std::vector<Node*>{});
  }

  TNode<BuiltinPtr> tmp13;
  TNode<BuiltinPtr> tmp14;
  TNode<BuiltinPtr> tmp15;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    std::tie(tmp13, tmp14, tmp15) = GetTypedArrayAccessor_Float64Elements_0(state_).Flatten();
    ca_.Goto(&block1, tmp13, tmp14, tmp15);
  }

  TNode<Int32T> tmp16;
  TNode<BoolT> tmp17;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp16 = FromConstexpr_ElementsKind_constexpr_UINT8_CLAMPED_ELEMENTS_0(state_, ElementsKind::UINT8_CLAMPED_ELEMENTS);
    tmp17 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{p_elementsKind}, TNode<Int32T>{tmp16});
    ca_.Branch(tmp17, &block14, std::vector<Node*>{}, &block15, std::vector<Node*>{});
  }

  TNode<BuiltinPtr> tmp18;
  TNode<BuiltinPtr> tmp19;
  TNode<BuiltinPtr> tmp20;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    std::tie(tmp18, tmp19, tmp20) = GetTypedArrayAccessor_Uint8ClampedElements_0(state_).Flatten();
    ca_.Goto(&block1, tmp18, tmp19, tmp20);
  }

  TNode<Int32T> tmp21;
  TNode<BoolT> tmp22;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp21 = FromConstexpr_ElementsKind_constexpr_BIGUINT64_ELEMENTS_0(state_, ElementsKind::BIGUINT64_ELEMENTS);
    tmp22 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{p_elementsKind}, TNode<Int32T>{tmp21});
    ca_.Branch(tmp22, &block17, std::vector<Node*>{}, &block18, std::vector<Node*>{});
  }

  TNode<BuiltinPtr> tmp23;
  TNode<BuiltinPtr> tmp24;
  TNode<BuiltinPtr> tmp25;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    std::tie(tmp23, tmp24, tmp25) = GetTypedArrayAccessor_BigUint64Elements_0(state_).Flatten();
    ca_.Goto(&block1, tmp23, tmp24, tmp25);
  }

  TNode<Int32T> tmp26;
  TNode<BoolT> tmp27;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp26 = FromConstexpr_ElementsKind_constexpr_BIGINT64_ELEMENTS_0(state_, ElementsKind::BIGINT64_ELEMENTS);
    tmp27 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{p_elementsKind}, TNode<Int32T>{tmp26});
    ca_.Branch(tmp27, &block20, std::vector<Node*>{}, &block21, std::vector<Node*>{});
  }

  TNode<BuiltinPtr> tmp28;
  TNode<BuiltinPtr> tmp29;
  TNode<BuiltinPtr> tmp30;
  if (block20.is_used()) {
    ca_.Bind(&block20);
    std::tie(tmp28, tmp29, tmp30) = GetTypedArrayAccessor_BigInt64Elements_0(state_).Flatten();
    ca_.Goto(&block1, tmp28, tmp29, tmp30);
  }

  if (block21.is_used()) {
    ca_.Bind(&block21);
    ca_.Goto(&block4);
  }

  TNode<Int32T> tmp31;
  TNode<BoolT> tmp32;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp31 = FromConstexpr_ElementsKind_constexpr_UINT8_ELEMENTS_0(state_, ElementsKind::UINT8_ELEMENTS);
    tmp32 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{p_elementsKind}, TNode<Int32T>{tmp31});
    ca_.Branch(tmp32, &block22, std::vector<Node*>{}, &block23, std::vector<Node*>{});
  }

  TNode<BuiltinPtr> tmp33;
  TNode<BuiltinPtr> tmp34;
  TNode<BuiltinPtr> tmp35;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    std::tie(tmp33, tmp34, tmp35) = GetTypedArrayAccessor_Uint8Elements_0(state_).Flatten();
    ca_.Goto(&block1, tmp33, tmp34, tmp35);
  }

  TNode<Int32T> tmp36;
  TNode<BoolT> tmp37;
  if (block23.is_used()) {
    ca_.Bind(&block23);
    tmp36 = FromConstexpr_ElementsKind_constexpr_INT8_ELEMENTS_0(state_, ElementsKind::INT8_ELEMENTS);
    tmp37 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{p_elementsKind}, TNode<Int32T>{tmp36});
    ca_.Branch(tmp37, &block25, std::vector<Node*>{}, &block26, std::vector<Node*>{});
  }

  TNode<BuiltinPtr> tmp38;
  TNode<BuiltinPtr> tmp39;
  TNode<BuiltinPtr> tmp40;
  if (block25.is_used()) {
    ca_.Bind(&block25);
    std::tie(tmp38, tmp39, tmp40) = GetTypedArrayAccessor_Int8Elements_0(state_).Flatten();
    ca_.Goto(&block1, tmp38, tmp39, tmp40);
  }

  TNode<Int32T> tmp41;
  TNode<BoolT> tmp42;
  if (block26.is_used()) {
    ca_.Bind(&block26);
    tmp41 = FromConstexpr_ElementsKind_constexpr_UINT16_ELEMENTS_0(state_, ElementsKind::UINT16_ELEMENTS);
    tmp42 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{p_elementsKind}, TNode<Int32T>{tmp41});
    ca_.Branch(tmp42, &block28, std::vector<Node*>{}, &block29, std::vector<Node*>{});
  }

  TNode<BuiltinPtr> tmp43;
  TNode<BuiltinPtr> tmp44;
  TNode<BuiltinPtr> tmp45;
  if (block28.is_used()) {
    ca_.Bind(&block28);
    std::tie(tmp43, tmp44, tmp45) = GetTypedArrayAccessor_Uint16Elements_0(state_).Flatten();
    ca_.Goto(&block1, tmp43, tmp44, tmp45);
  }

  TNode<Int32T> tmp46;
  TNode<BoolT> tmp47;
  if (block29.is_used()) {
    ca_.Bind(&block29);
    tmp46 = FromConstexpr_ElementsKind_constexpr_INT16_ELEMENTS_0(state_, ElementsKind::INT16_ELEMENTS);
    tmp47 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{p_elementsKind}, TNode<Int32T>{tmp46});
    ca_.Branch(tmp47, &block31, std::vector<Node*>{}, &block32, std::vector<Node*>{});
  }

  TNode<BuiltinPtr> tmp48;
  TNode<BuiltinPtr> tmp49;
  TNode<BuiltinPtr> tmp50;
  if (block31.is_used()) {
    ca_.Bind(&block31);
    std::tie(tmp48, tmp49, tmp50) = GetTypedArrayAccessor_Int16Elements_0(state_).Flatten();
    ca_.Goto(&block1, tmp48, tmp49, tmp50);
  }

  TNode<Int32T> tmp51;
  TNode<BoolT> tmp52;
  if (block32.is_used()) {
    ca_.Bind(&block32);
    tmp51 = FromConstexpr_ElementsKind_constexpr_UINT32_ELEMENTS_0(state_, ElementsKind::UINT32_ELEMENTS);
    tmp52 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{p_elementsKind}, TNode<Int32T>{tmp51});
    ca_.Branch(tmp52, &block34, std::vector<Node*>{}, &block35, std::vector<Node*>{});
  }

  TNode<BuiltinPtr> tmp53;
  TNode<BuiltinPtr> tmp54;
  TNode<BuiltinPtr> tmp55;
  if (block34.is_used()) {
    ca_.Bind(&block34);
    std::tie(tmp53, tmp54, tmp55) = GetTypedArrayAccessor_Uint32Elements_0(state_).Flatten();
    ca_.Goto(&block1, tmp53, tmp54, tmp55);
  }

  if (block35.is_used()) {
    ca_.Bind(&block35);
    ca_.Goto(&block4);
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BuiltinPtr> phi_bb1_1;
  TNode<BuiltinPtr> phi_bb1_2;
  TNode<BuiltinPtr> phi_bb1_3;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_1, &phi_bb1_2, &phi_bb1_3);
    ca_.Goto(&block36);
  }

    ca_.Bind(&block36);
  return TorqueStructTypedArrayAccessor_0{TNode<BuiltinPtr>{phi_bb1_1}, TNode<BuiltinPtr>{phi_bb1_2}, TNode<BuiltinPtr>{phi_bb1_3}};
}

TNode<JSTypedArray> EnsureAttached_0(compiler::CodeAssemblerState* state_, TNode<JSTypedArray> p_array, compiler::CodeAssemblerLabel* label_Detached) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSArrayBuffer> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSArrayBuffer>(CodeStubAssembler::Reference{p_array, tmp0});
    tmp2 = IsDetachedBuffer_0(state_, TNode<JSArrayBuffer>{tmp1});
    ca_.Branch(tmp2, &block3, std::vector<Node*>{}, &block4, std::vector<Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(label_Detached);
  }

  TNode<JSTypedArray> tmp3;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp3 = (TNode<JSTypedArray>{p_array});
    ca_.Goto(&block5);
  }

    ca_.Bind(&block5);
  return TNode<JSTypedArray>{tmp3};
}

TorqueStructAttachedJSTypedArrayWitness_0 NewAttachedJSTypedArrayWitness_0(compiler::CodeAssemblerState* state_, TNode<JSTypedArray> p_array) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Int32T> tmp0;
  TNode<BuiltinPtr> tmp1;
  TNode<BuiltinPtr> tmp2;
  TNode<BuiltinPtr> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).LoadElementsKind(TNode<JSTypedArray>{p_array});
    std::tie(tmp1, tmp2, tmp3) = GetTypedArrayAccessor_0(state_, TNode<Int32T>{tmp0}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructAttachedJSTypedArrayWitness_0{TNode<JSTypedArray>{p_array}, TNode<JSTypedArray>{p_array}, TNode<BuiltinPtr>{tmp1}};
}

ElementsKind KindForArrayType_Uint8Elements_0(compiler::CodeAssemblerState* state_) {
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
  return ElementsKind::UINT8_ELEMENTS;
}

ElementsKind KindForArrayType_Int8Elements_0(compiler::CodeAssemblerState* state_) {
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
  return ElementsKind::INT8_ELEMENTS;
}

ElementsKind KindForArrayType_Uint16Elements_0(compiler::CodeAssemblerState* state_) {
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
  return ElementsKind::UINT16_ELEMENTS;
}

ElementsKind KindForArrayType_Int16Elements_0(compiler::CodeAssemblerState* state_) {
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
  return ElementsKind::INT16_ELEMENTS;
}

ElementsKind KindForArrayType_Uint32Elements_0(compiler::CodeAssemblerState* state_) {
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
  return ElementsKind::UINT32_ELEMENTS;
}

ElementsKind KindForArrayType_Int32Elements_0(compiler::CodeAssemblerState* state_) {
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
  return ElementsKind::INT32_ELEMENTS;
}

ElementsKind KindForArrayType_Float32Elements_0(compiler::CodeAssemblerState* state_) {
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
  return ElementsKind::FLOAT32_ELEMENTS;
}

ElementsKind KindForArrayType_Float64Elements_0(compiler::CodeAssemblerState* state_) {
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
  return ElementsKind::FLOAT64_ELEMENTS;
}

ElementsKind KindForArrayType_Uint8ClampedElements_0(compiler::CodeAssemblerState* state_) {
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
  return ElementsKind::UINT8_CLAMPED_ELEMENTS;
}

ElementsKind KindForArrayType_BigUint64Elements_0(compiler::CodeAssemblerState* state_) {
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
  return ElementsKind::BIGUINT64_ELEMENTS;
}

ElementsKind KindForArrayType_BigInt64Elements_0(compiler::CodeAssemblerState* state_) {
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
  return ElementsKind::BIGINT64_ELEMENTS;
}

TorqueStructTypedArrayAccessor_0 GetTypedArrayAccessor_Int32Elements_0(compiler::CodeAssemblerState* state_) {
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
  return TorqueStructTypedArrayAccessor_0{TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kLoadTypedElement_Int32Elements_0))}, TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStoreTypedElementNumeric_Int32Elements_0))}, TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStoreTypedElementJSAny_Int32Elements_0))}};
}

TorqueStructTypedArrayAccessor_0 GetTypedArrayAccessor_Float32Elements_0(compiler::CodeAssemblerState* state_) {
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
  return TorqueStructTypedArrayAccessor_0{TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kLoadTypedElement_Float32Elements_0))}, TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStoreTypedElementNumeric_Float32Elements_0))}, TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStoreTypedElementJSAny_Float32Elements_0))}};
}

TorqueStructTypedArrayAccessor_0 GetTypedArrayAccessor_Float64Elements_0(compiler::CodeAssemblerState* state_) {
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
  return TorqueStructTypedArrayAccessor_0{TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kLoadTypedElement_Float64Elements_0))}, TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStoreTypedElementNumeric_Float64Elements_0))}, TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStoreTypedElementJSAny_Float64Elements_0))}};
}

TorqueStructTypedArrayAccessor_0 GetTypedArrayAccessor_Uint8ClampedElements_0(compiler::CodeAssemblerState* state_) {
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
  return TorqueStructTypedArrayAccessor_0{TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kLoadTypedElement_Uint8ClampedElements_0))}, TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStoreTypedElementNumeric_Uint8ClampedElements_0))}, TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStoreTypedElementJSAny_Uint8ClampedElements_0))}};
}

TorqueStructTypedArrayAccessor_0 GetTypedArrayAccessor_BigUint64Elements_0(compiler::CodeAssemblerState* state_) {
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
  return TorqueStructTypedArrayAccessor_0{TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kLoadTypedElement_BigUint64Elements_0))}, TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStoreTypedElementNumeric_BigUint64Elements_0))}, TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStoreTypedElementJSAny_BigUint64Elements_0))}};
}

TorqueStructTypedArrayAccessor_0 GetTypedArrayAccessor_BigInt64Elements_0(compiler::CodeAssemblerState* state_) {
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
  return TorqueStructTypedArrayAccessor_0{TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kLoadTypedElement_BigInt64Elements_0))}, TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStoreTypedElementNumeric_BigInt64Elements_0))}, TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStoreTypedElementJSAny_BigInt64Elements_0))}};
}

TorqueStructTypedArrayAccessor_0 GetTypedArrayAccessor_Uint8Elements_0(compiler::CodeAssemblerState* state_) {
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
  return TorqueStructTypedArrayAccessor_0{TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kLoadTypedElement_Uint8Elements_0))}, TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStoreTypedElementNumeric_Uint8Elements_0))}, TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStoreTypedElementJSAny_Uint8Elements_0))}};
}

TorqueStructTypedArrayAccessor_0 GetTypedArrayAccessor_Int8Elements_0(compiler::CodeAssemblerState* state_) {
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
  return TorqueStructTypedArrayAccessor_0{TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kLoadTypedElement_Int8Elements_0))}, TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStoreTypedElementNumeric_Int8Elements_0))}, TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStoreTypedElementJSAny_Int8Elements_0))}};
}

TorqueStructTypedArrayAccessor_0 GetTypedArrayAccessor_Uint16Elements_0(compiler::CodeAssemblerState* state_) {
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
  return TorqueStructTypedArrayAccessor_0{TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kLoadTypedElement_Uint16Elements_0))}, TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStoreTypedElementNumeric_Uint16Elements_0))}, TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStoreTypedElementJSAny_Uint16Elements_0))}};
}

TorqueStructTypedArrayAccessor_0 GetTypedArrayAccessor_Int16Elements_0(compiler::CodeAssemblerState* state_) {
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
  return TorqueStructTypedArrayAccessor_0{TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kLoadTypedElement_Int16Elements_0))}, TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStoreTypedElementNumeric_Int16Elements_0))}, TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStoreTypedElementJSAny_Int16Elements_0))}};
}

TorqueStructTypedArrayAccessor_0 GetTypedArrayAccessor_Uint32Elements_0(compiler::CodeAssemblerState* state_) {
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
  return TorqueStructTypedArrayAccessor_0{TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kLoadTypedElement_Uint32Elements_0))}, TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStoreTypedElementNumeric_Uint32Elements_0))}, TNode<BuiltinPtr>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStoreTypedElementJSAny_Uint32Elements_0))}};
}

TF_BUILTIN(LoadTypedElement_Int32Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<JSTypedArray> parameter0 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter0);
  TNode<UintPtrT> parameter1 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<Numeric> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{parameter0});
    tmp1 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp0}, TNode<UintPtrT>{parameter1}, (KindForArrayType_Int32Elements_0(state_)));
    CodeStubAssembler(state_).Return(tmp1);
  }
}

TF_BUILTIN(StoreTypedElementNumeric_Int32Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSTypedArray> parameter1 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Numeric> parameter3 = UncheckedCast<Numeric>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    TypedArrayBuiltinsAssembler(state_).StoreJSTypedArrayElementFromNumeric(TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<Numeric>{parameter3}, (KindForArrayType_Int32Elements_0(state_)));
    tmp0 = kStoreSucceded_0(state_);
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TF_BUILTIN(StoreTypedElementJSAny_Int32Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSTypedArray> parameter1 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label0(&ca_);
    TypedArrayBuiltinsAssembler(state_).StoreJSTypedArrayElementFromTagged(TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<Object>{parameter3}, (KindForArrayType_Int32Elements_0(state_)), &label0);
    ca_.Goto(&block3);
    if (label0.is_used()) {
      ca_.Bind(&label0);
      ca_.Goto(&block4);
    }
  }

  TNode<Smi> tmp1;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp1 = kStoreFailureArrayDetached_0(state_);
    CodeStubAssembler(state_).Return(tmp1);
  }

  TNode<Smi> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = kStoreSucceded_0(state_);
    CodeStubAssembler(state_).Return(tmp2);
  }
}

TF_BUILTIN(LoadTypedElement_Float32Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<JSTypedArray> parameter0 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter0);
  TNode<UintPtrT> parameter1 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<Numeric> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{parameter0});
    tmp1 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp0}, TNode<UintPtrT>{parameter1}, (KindForArrayType_Float32Elements_0(state_)));
    CodeStubAssembler(state_).Return(tmp1);
  }
}

TF_BUILTIN(StoreTypedElementNumeric_Float32Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSTypedArray> parameter1 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Numeric> parameter3 = UncheckedCast<Numeric>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    TypedArrayBuiltinsAssembler(state_).StoreJSTypedArrayElementFromNumeric(TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<Numeric>{parameter3}, (KindForArrayType_Float32Elements_0(state_)));
    tmp0 = kStoreSucceded_0(state_);
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TF_BUILTIN(StoreTypedElementJSAny_Float32Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSTypedArray> parameter1 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label0(&ca_);
    TypedArrayBuiltinsAssembler(state_).StoreJSTypedArrayElementFromTagged(TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<Object>{parameter3}, (KindForArrayType_Float32Elements_0(state_)), &label0);
    ca_.Goto(&block3);
    if (label0.is_used()) {
      ca_.Bind(&label0);
      ca_.Goto(&block4);
    }
  }

  TNode<Smi> tmp1;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp1 = kStoreFailureArrayDetached_0(state_);
    CodeStubAssembler(state_).Return(tmp1);
  }

  TNode<Smi> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = kStoreSucceded_0(state_);
    CodeStubAssembler(state_).Return(tmp2);
  }
}

TF_BUILTIN(LoadTypedElement_Float64Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<JSTypedArray> parameter0 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter0);
  TNode<UintPtrT> parameter1 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<Numeric> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{parameter0});
    tmp1 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp0}, TNode<UintPtrT>{parameter1}, (KindForArrayType_Float64Elements_0(state_)));
    CodeStubAssembler(state_).Return(tmp1);
  }
}

TF_BUILTIN(StoreTypedElementNumeric_Float64Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSTypedArray> parameter1 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Numeric> parameter3 = UncheckedCast<Numeric>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    TypedArrayBuiltinsAssembler(state_).StoreJSTypedArrayElementFromNumeric(TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<Numeric>{parameter3}, (KindForArrayType_Float64Elements_0(state_)));
    tmp0 = kStoreSucceded_0(state_);
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TF_BUILTIN(StoreTypedElementJSAny_Float64Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSTypedArray> parameter1 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label0(&ca_);
    TypedArrayBuiltinsAssembler(state_).StoreJSTypedArrayElementFromTagged(TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<Object>{parameter3}, (KindForArrayType_Float64Elements_0(state_)), &label0);
    ca_.Goto(&block3);
    if (label0.is_used()) {
      ca_.Bind(&label0);
      ca_.Goto(&block4);
    }
  }

  TNode<Smi> tmp1;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp1 = kStoreFailureArrayDetached_0(state_);
    CodeStubAssembler(state_).Return(tmp1);
  }

  TNode<Smi> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = kStoreSucceded_0(state_);
    CodeStubAssembler(state_).Return(tmp2);
  }
}

TF_BUILTIN(LoadTypedElement_Uint8ClampedElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<JSTypedArray> parameter0 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter0);
  TNode<UintPtrT> parameter1 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<Numeric> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{parameter0});
    tmp1 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp0}, TNode<UintPtrT>{parameter1}, (KindForArrayType_Uint8ClampedElements_0(state_)));
    CodeStubAssembler(state_).Return(tmp1);
  }
}

TF_BUILTIN(StoreTypedElementNumeric_Uint8ClampedElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSTypedArray> parameter1 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Numeric> parameter3 = UncheckedCast<Numeric>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    TypedArrayBuiltinsAssembler(state_).StoreJSTypedArrayElementFromNumeric(TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<Numeric>{parameter3}, (KindForArrayType_Uint8ClampedElements_0(state_)));
    tmp0 = kStoreSucceded_0(state_);
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TF_BUILTIN(StoreTypedElementJSAny_Uint8ClampedElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSTypedArray> parameter1 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label0(&ca_);
    TypedArrayBuiltinsAssembler(state_).StoreJSTypedArrayElementFromTagged(TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<Object>{parameter3}, (KindForArrayType_Uint8ClampedElements_0(state_)), &label0);
    ca_.Goto(&block3);
    if (label0.is_used()) {
      ca_.Bind(&label0);
      ca_.Goto(&block4);
    }
  }

  TNode<Smi> tmp1;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp1 = kStoreFailureArrayDetached_0(state_);
    CodeStubAssembler(state_).Return(tmp1);
  }

  TNode<Smi> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = kStoreSucceded_0(state_);
    CodeStubAssembler(state_).Return(tmp2);
  }
}

TF_BUILTIN(LoadTypedElement_BigUint64Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<JSTypedArray> parameter0 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter0);
  TNode<UintPtrT> parameter1 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<Numeric> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{parameter0});
    tmp1 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp0}, TNode<UintPtrT>{parameter1}, (KindForArrayType_BigUint64Elements_0(state_)));
    CodeStubAssembler(state_).Return(tmp1);
  }
}

TF_BUILTIN(StoreTypedElementNumeric_BigUint64Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSTypedArray> parameter1 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Numeric> parameter3 = UncheckedCast<Numeric>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    TypedArrayBuiltinsAssembler(state_).StoreJSTypedArrayElementFromNumeric(TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<Numeric>{parameter3}, (KindForArrayType_BigUint64Elements_0(state_)));
    tmp0 = kStoreSucceded_0(state_);
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TF_BUILTIN(StoreTypedElementJSAny_BigUint64Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSTypedArray> parameter1 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label0(&ca_);
    TypedArrayBuiltinsAssembler(state_).StoreJSTypedArrayElementFromTagged(TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<Object>{parameter3}, (KindForArrayType_BigUint64Elements_0(state_)), &label0);
    ca_.Goto(&block3);
    if (label0.is_used()) {
      ca_.Bind(&label0);
      ca_.Goto(&block4);
    }
  }

  TNode<Smi> tmp1;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp1 = kStoreFailureArrayDetached_0(state_);
    CodeStubAssembler(state_).Return(tmp1);
  }

  TNode<Smi> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = kStoreSucceded_0(state_);
    CodeStubAssembler(state_).Return(tmp2);
  }
}

TF_BUILTIN(LoadTypedElement_BigInt64Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<JSTypedArray> parameter0 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter0);
  TNode<UintPtrT> parameter1 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<Numeric> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{parameter0});
    tmp1 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp0}, TNode<UintPtrT>{parameter1}, (KindForArrayType_BigInt64Elements_0(state_)));
    CodeStubAssembler(state_).Return(tmp1);
  }
}

TF_BUILTIN(StoreTypedElementNumeric_BigInt64Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSTypedArray> parameter1 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Numeric> parameter3 = UncheckedCast<Numeric>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    TypedArrayBuiltinsAssembler(state_).StoreJSTypedArrayElementFromNumeric(TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<Numeric>{parameter3}, (KindForArrayType_BigInt64Elements_0(state_)));
    tmp0 = kStoreSucceded_0(state_);
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TF_BUILTIN(StoreTypedElementJSAny_BigInt64Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSTypedArray> parameter1 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label0(&ca_);
    TypedArrayBuiltinsAssembler(state_).StoreJSTypedArrayElementFromTagged(TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<Object>{parameter3}, (KindForArrayType_BigInt64Elements_0(state_)), &label0);
    ca_.Goto(&block3);
    if (label0.is_used()) {
      ca_.Bind(&label0);
      ca_.Goto(&block4);
    }
  }

  TNode<Smi> tmp1;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp1 = kStoreFailureArrayDetached_0(state_);
    CodeStubAssembler(state_).Return(tmp1);
  }

  TNode<Smi> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = kStoreSucceded_0(state_);
    CodeStubAssembler(state_).Return(tmp2);
  }
}

TF_BUILTIN(LoadTypedElement_Uint8Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<JSTypedArray> parameter0 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter0);
  TNode<UintPtrT> parameter1 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<Numeric> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{parameter0});
    tmp1 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp0}, TNode<UintPtrT>{parameter1}, (KindForArrayType_Uint8Elements_0(state_)));
    CodeStubAssembler(state_).Return(tmp1);
  }
}

TF_BUILTIN(StoreTypedElementNumeric_Uint8Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSTypedArray> parameter1 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Numeric> parameter3 = UncheckedCast<Numeric>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    TypedArrayBuiltinsAssembler(state_).StoreJSTypedArrayElementFromNumeric(TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<Numeric>{parameter3}, (KindForArrayType_Uint8Elements_0(state_)));
    tmp0 = kStoreSucceded_0(state_);
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TF_BUILTIN(StoreTypedElementJSAny_Uint8Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSTypedArray> parameter1 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label0(&ca_);
    TypedArrayBuiltinsAssembler(state_).StoreJSTypedArrayElementFromTagged(TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<Object>{parameter3}, (KindForArrayType_Uint8Elements_0(state_)), &label0);
    ca_.Goto(&block3);
    if (label0.is_used()) {
      ca_.Bind(&label0);
      ca_.Goto(&block4);
    }
  }

  TNode<Smi> tmp1;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp1 = kStoreFailureArrayDetached_0(state_);
    CodeStubAssembler(state_).Return(tmp1);
  }

  TNode<Smi> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = kStoreSucceded_0(state_);
    CodeStubAssembler(state_).Return(tmp2);
  }
}

TF_BUILTIN(LoadTypedElement_Int8Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<JSTypedArray> parameter0 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter0);
  TNode<UintPtrT> parameter1 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<Numeric> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{parameter0});
    tmp1 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp0}, TNode<UintPtrT>{parameter1}, (KindForArrayType_Int8Elements_0(state_)));
    CodeStubAssembler(state_).Return(tmp1);
  }
}

TF_BUILTIN(StoreTypedElementNumeric_Int8Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSTypedArray> parameter1 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Numeric> parameter3 = UncheckedCast<Numeric>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    TypedArrayBuiltinsAssembler(state_).StoreJSTypedArrayElementFromNumeric(TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<Numeric>{parameter3}, (KindForArrayType_Int8Elements_0(state_)));
    tmp0 = kStoreSucceded_0(state_);
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TF_BUILTIN(StoreTypedElementJSAny_Int8Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSTypedArray> parameter1 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label0(&ca_);
    TypedArrayBuiltinsAssembler(state_).StoreJSTypedArrayElementFromTagged(TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<Object>{parameter3}, (KindForArrayType_Int8Elements_0(state_)), &label0);
    ca_.Goto(&block3);
    if (label0.is_used()) {
      ca_.Bind(&label0);
      ca_.Goto(&block4);
    }
  }

  TNode<Smi> tmp1;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp1 = kStoreFailureArrayDetached_0(state_);
    CodeStubAssembler(state_).Return(tmp1);
  }

  TNode<Smi> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = kStoreSucceded_0(state_);
    CodeStubAssembler(state_).Return(tmp2);
  }
}

TF_BUILTIN(LoadTypedElement_Uint16Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<JSTypedArray> parameter0 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter0);
  TNode<UintPtrT> parameter1 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<Numeric> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{parameter0});
    tmp1 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp0}, TNode<UintPtrT>{parameter1}, (KindForArrayType_Uint16Elements_0(state_)));
    CodeStubAssembler(state_).Return(tmp1);
  }
}

TF_BUILTIN(StoreTypedElementNumeric_Uint16Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSTypedArray> parameter1 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Numeric> parameter3 = UncheckedCast<Numeric>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    TypedArrayBuiltinsAssembler(state_).StoreJSTypedArrayElementFromNumeric(TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<Numeric>{parameter3}, (KindForArrayType_Uint16Elements_0(state_)));
    tmp0 = kStoreSucceded_0(state_);
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TF_BUILTIN(StoreTypedElementJSAny_Uint16Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSTypedArray> parameter1 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label0(&ca_);
    TypedArrayBuiltinsAssembler(state_).StoreJSTypedArrayElementFromTagged(TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<Object>{parameter3}, (KindForArrayType_Uint16Elements_0(state_)), &label0);
    ca_.Goto(&block3);
    if (label0.is_used()) {
      ca_.Bind(&label0);
      ca_.Goto(&block4);
    }
  }

  TNode<Smi> tmp1;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp1 = kStoreFailureArrayDetached_0(state_);
    CodeStubAssembler(state_).Return(tmp1);
  }

  TNode<Smi> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = kStoreSucceded_0(state_);
    CodeStubAssembler(state_).Return(tmp2);
  }
}

TF_BUILTIN(LoadTypedElement_Int16Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<JSTypedArray> parameter0 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter0);
  TNode<UintPtrT> parameter1 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<Numeric> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{parameter0});
    tmp1 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp0}, TNode<UintPtrT>{parameter1}, (KindForArrayType_Int16Elements_0(state_)));
    CodeStubAssembler(state_).Return(tmp1);
  }
}

TF_BUILTIN(StoreTypedElementNumeric_Int16Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSTypedArray> parameter1 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Numeric> parameter3 = UncheckedCast<Numeric>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    TypedArrayBuiltinsAssembler(state_).StoreJSTypedArrayElementFromNumeric(TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<Numeric>{parameter3}, (KindForArrayType_Int16Elements_0(state_)));
    tmp0 = kStoreSucceded_0(state_);
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TF_BUILTIN(StoreTypedElementJSAny_Int16Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSTypedArray> parameter1 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label0(&ca_);
    TypedArrayBuiltinsAssembler(state_).StoreJSTypedArrayElementFromTagged(TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<Object>{parameter3}, (KindForArrayType_Int16Elements_0(state_)), &label0);
    ca_.Goto(&block3);
    if (label0.is_used()) {
      ca_.Bind(&label0);
      ca_.Goto(&block4);
    }
  }

  TNode<Smi> tmp1;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp1 = kStoreFailureArrayDetached_0(state_);
    CodeStubAssembler(state_).Return(tmp1);
  }

  TNode<Smi> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = kStoreSucceded_0(state_);
    CodeStubAssembler(state_).Return(tmp2);
  }
}

TF_BUILTIN(LoadTypedElement_Uint32Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<JSTypedArray> parameter0 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter0);
  TNode<UintPtrT> parameter1 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<Numeric> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{parameter0});
    tmp1 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp0}, TNode<UintPtrT>{parameter1}, (KindForArrayType_Uint32Elements_0(state_)));
    CodeStubAssembler(state_).Return(tmp1);
  }
}

TF_BUILTIN(StoreTypedElementNumeric_Uint32Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSTypedArray> parameter1 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Numeric> parameter3 = UncheckedCast<Numeric>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    TypedArrayBuiltinsAssembler(state_).StoreJSTypedArrayElementFromNumeric(TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<Numeric>{parameter3}, (KindForArrayType_Uint32Elements_0(state_)));
    tmp0 = kStoreSucceded_0(state_);
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TF_BUILTIN(StoreTypedElementJSAny_Uint32Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSTypedArray> parameter1 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label0(&ca_);
    TypedArrayBuiltinsAssembler(state_).StoreJSTypedArrayElementFromTagged(TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<Object>{parameter3}, (KindForArrayType_Uint32Elements_0(state_)), &label0);
    ca_.Goto(&block3);
    if (label0.is_used()) {
      ca_.Bind(&label0);
      ca_.Goto(&block4);
    }
  }

  TNode<Smi> tmp1;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp1 = kStoreFailureArrayDetached_0(state_);
    CodeStubAssembler(state_).Return(tmp1);
  }

  TNode<Smi> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = kStoreSucceded_0(state_);
    CodeStubAssembler(state_).Return(tmp2);
  }
}

}  // namespace internal
}  // namespace v8

