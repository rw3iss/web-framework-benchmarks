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

TNode<Object> TryFastArrayShift_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_receiver, compiler::CodeAssemblerLabel* label_Slow, compiler::CodeAssemblerLabel* label_Runtime) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block48(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block57(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block56(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block62(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block63(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block52(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block68(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block67(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block73(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block74(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block53(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block76(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSArray> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_FastJSArray_1(state_, TNode<Context>{p_context}, TNode<Object>{p_receiver}, &label1);
    ca_.Goto(&block4);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block5);
    }
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    ca_.Goto(&block1);
  }

  TNode<JSArray> tmp2;
  TNode<JSArray> tmp3;
  TNode<Map> tmp4;
  TNode<BoolT> tmp5;
  TNode<BoolT> tmp6;
  TNode<BoolT> tmp7;
  TNode<Int32T> tmp8;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    std::tie(tmp2, tmp3, tmp4, tmp5, tmp6, tmp7) = NewFastJSArrayWitness_0(state_, TNode<JSArray>{tmp0}).Flatten();
    compiler::CodeAssemblerLabel label9(&ca_);
    tmp8 = CodeStubAssembler(state_).EnsureArrayPushable(TNode<Context>{p_context}, TNode<Map>{tmp4}, &label9);
    ca_.Goto(&block7);
    if (label9.is_used()) {
      ca_.Bind(&label9);
      ca_.Goto(&block8);
    }
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block1);
  }

  TNode<BoolT> tmp10;
  TNode<Smi> tmp11;
  TNode<Smi> tmp12;
  TNode<BoolT> tmp13;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    EnsureWriteableFastElements_0(state_, TNode<Context>{p_context}, TNode<JSArray>{tmp3});
    tmp10 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    tmp11 = CodeStubAssembler(state_).LoadFastJSArrayLength(TNode<JSArray>{tmp0});
    tmp12 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp13 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp11}, TNode<Smi>{tmp12});
    ca_.Branch(tmp13, &block9, std::vector<Node*>{}, &block10, std::vector<Node*>{});
  }

  TNode<Oddball> tmp14;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp14 = Undefined_0(state_);
    ca_.Goto(&block3, tmp14);
  }

  TNode<Smi> tmp15;
  TNode<Smi> tmp16;
  TNode<Smi> tmp17;
  TNode<Smi> tmp18;
  TNode<Smi> tmp19;
  TNode<Smi> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<FixedArrayBase> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<Smi> tmp24;
  TNode<BoolT> tmp25;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp15 = CodeStubAssembler(state_).LoadFastJSArrayLength(TNode<JSArray>{tmp0});
    tmp16 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp17 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp15}, TNode<Smi>{tmp16});
    tmp18 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp17}, TNode<Smi>{tmp17});
    tmp19 = FromConstexpr_Smi_constexpr_int31_0(state_, JSObject::kMinAddedElementsCapacity);
    tmp20 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp18}, TNode<Smi>{tmp19});
    tmp21 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp22 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp0, tmp21});
    tmp23 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp24 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp22, tmp23});
    tmp25 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp20}, TNode<Smi>{tmp24});
    ca_.Branch(tmp25, &block11, std::vector<Node*>{}, &block12, std::vector<Node*>{});
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    ca_.Goto(&block2);
  }

  TNode<Smi> tmp26;
  TNode<BoolT> tmp27;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp26 = FromConstexpr_Smi_constexpr_int31_0(state_, JSArray::kMaxCopyElements);
    tmp27 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp17}, TNode<Smi>{tmp26});
    ca_.Branch(tmp27, &block13, std::vector<Node*>{}, &block14, std::vector<Node*>{});
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    ca_.Goto(&block2);
  }

  TNode<Smi> tmp28;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp28 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    ca_.Branch(tmp5, &block19, std::vector<Node*>{}, &block20, std::vector<Node*>{});
  }

  TNode<Object> tmp29;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    compiler::CodeAssemblerLabel label30(&ca_);
    tmp29 = LoadElementNoHole_FixedDoubleArray_0(state_, TNode<Context>{p_context}, TNode<JSArray>{tmp3}, TNode<Smi>{tmp28}, &label30);
    ca_.Goto(&block22);
    if (label30.is_used()) {
      ca_.Bind(&label30);
      ca_.Goto(&block23);
    }
  }

  if (block23.is_used()) {
    ca_.Bind(&block23);
    ca_.Goto(&block17);
  }

  if (block22.is_used()) {
    ca_.Bind(&block22);
    ca_.Goto(&block18, tmp29);
  }

  TNode<Object> tmp31;
  if (block20.is_used()) {
    ca_.Bind(&block20);
    compiler::CodeAssemblerLabel label32(&ca_);
    tmp31 = LoadElementNoHole_FixedArray_0(state_, TNode<Context>{p_context}, TNode<JSArray>{tmp3}, TNode<Smi>{tmp28}, &label32);
    ca_.Goto(&block24);
    if (label32.is_used()) {
      ca_.Bind(&label32);
      ca_.Goto(&block25);
    }
  }

  if (block25.is_used()) {
    ca_.Bind(&block25);
    ca_.Goto(&block17);
  }

  if (block24.is_used()) {
    ca_.Bind(&block24);
    ca_.Goto(&block18, tmp31);
  }

  TNode<Object> phi_bb18_17;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_17);
    ca_.Goto(&block15, phi_bb18_17);
  }

  TNode<Oddball> tmp33;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp33 = Undefined_0(state_);
    ca_.Goto(&block15, tmp33);
  }

  TNode<Object> phi_bb15_13;
  TNode<IntPtrT> tmp34;
  TNode<IntPtrT> tmp35;
  TNode<IntPtrT> tmp36;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_13);
    StoreFastJSArrayLength_0(state_, TNode<JSArray>{tmp3}, TNode<Smi>{tmp17});
    tmp34 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp17});
    tmp35 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp36 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    ca_.Branch(tmp5, &block36, std::vector<Node*>{}, &block37, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp37;
  TNode<FixedArrayBase> tmp38;
  TNode<FixedDoubleArray> tmp39;
  if (block36.is_used()) {
    ca_.Bind(&block36);
    tmp37 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp38 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp3, tmp37});
    compiler::CodeAssemblerLabel label40(&ca_);
    tmp39 = Cast_FixedDoubleArray_0(state_, TNode<HeapObject>{tmp38}, &label40);
    ca_.Goto(&block41);
    if (label40.is_used()) {
      ca_.Bind(&label40);
      ca_.Goto(&block42);
    }
  }

  if (block42.is_used()) {
    ca_.Bind(&block42);
    CodeStubAssembler(state_).Unreachable();
  }

  if (block41.is_used()) {
    ca_.Bind(&block41);
    TorqueMoveElements_1(state_, TNode<FixedDoubleArray>{tmp39}, TNode<IntPtrT>{tmp35}, TNode<IntPtrT>{tmp36}, TNode<IntPtrT>{tmp34});
    ca_.Goto(&block38);
  }

  TNode<IntPtrT> tmp41;
  TNode<FixedArrayBase> tmp42;
  TNode<FixedArray> tmp43;
  if (block37.is_used()) {
    ca_.Bind(&block37);
    tmp41 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp42 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp3, tmp41});
    compiler::CodeAssemblerLabel label44(&ca_);
    tmp43 = Cast_FixedArray_0(state_, TNode<HeapObject>{tmp42}, &label44);
    ca_.Goto(&block45);
    if (label44.is_used()) {
      ca_.Bind(&label44);
      ca_.Goto(&block46);
    }
  }

  if (block46.is_used()) {
    ca_.Bind(&block46);
    CodeStubAssembler(state_).Unreachable();
  }

  if (block45.is_used()) {
    ca_.Bind(&block45);
    ca_.Branch(tmp6, &block47, std::vector<Node*>{}, &block48, std::vector<Node*>{});
  }

  if (block47.is_used()) {
    ca_.Bind(&block47);
    TorqueMoveElementsSmi_0(state_, TNode<FixedArray>{tmp43}, TNode<IntPtrT>{tmp35}, TNode<IntPtrT>{tmp36}, TNode<IntPtrT>{tmp34});
    ca_.Goto(&block49);
  }

  if (block48.is_used()) {
    ca_.Bind(&block48);
    TorqueMoveElements_0(state_, TNode<FixedArray>{tmp43}, TNode<IntPtrT>{tmp35}, TNode<IntPtrT>{tmp36}, TNode<IntPtrT>{tmp34});
    ca_.Goto(&block49);
  }

  if (block49.is_used()) {
    ca_.Bind(&block49);
    ca_.Goto(&block38);
  }

  if (block38.is_used()) {
    ca_.Bind(&block38);
    ca_.Branch(tmp5, &block51, std::vector<Node*>{}, &block52, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp45;
  TNode<FixedArrayBase> tmp46;
  TNode<FixedDoubleArray> tmp47;
  if (block51.is_used()) {
    ca_.Bind(&block51);
    tmp45 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp46 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp3, tmp45});
    compiler::CodeAssemblerLabel label48(&ca_);
    tmp47 = Cast_FixedDoubleArray_0(state_, TNode<HeapObject>{tmp46}, &label48);
    ca_.Goto(&block56);
    if (label48.is_used()) {
      ca_.Bind(&label48);
      ca_.Goto(&block57);
    }
  }

  if (block57.is_used()) {
    ca_.Bind(&block57);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp49;
  TNode<IntPtrT> tmp50;
  TNode<IntPtrT> tmp51;
  TNode<Smi> tmp52;
  TNode<IntPtrT> tmp53;
  TNode<IntPtrT> tmp54;
  TNode<UintPtrT> tmp55;
  TNode<UintPtrT> tmp56;
  TNode<BoolT> tmp57;
  if (block56.is_used()) {
    ca_.Bind(&block56);
    tmp49 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp50 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp51 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp52 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp47, tmp51});
    tmp53 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp52});
    tmp54 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp17});
    tmp55 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp54});
    tmp56 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp53});
    tmp57 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp55}, TNode<UintPtrT>{tmp56});
    ca_.Branch(tmp57, &block62, std::vector<Node*>{}, &block63, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp58;
  TNode<IntPtrT> tmp59;
  TNode<IntPtrT> tmp60;
  TNode<HeapObject> tmp61;
  TNode<IntPtrT> tmp62;
  TNode<BoolT> tmp63;
  TNode<Float64T> tmp64;
  if (block62.is_used()) {
    ca_.Bind(&block62);
    tmp58 = FromConstexpr_intptr_constexpr_int31_0(state_, kDoubleSize);
    tmp59 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp54}, TNode<IntPtrT>{tmp58});
    tmp60 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp49}, TNode<IntPtrT>{tmp59});
    std::tie(tmp61, tmp62) = NewReference_float64_or_hole_0(state_, TNode<HeapObject>{tmp47}, TNode<IntPtrT>{tmp60}).Flatten();
    std::tie(tmp63, tmp64) = kDoubleHole_0(state_).Flatten();
    StoreFloat64OrHole_0(state_, TorqueStructReference_float64_or_hole_0{TNode<HeapObject>{tmp61}, TNode<IntPtrT>{tmp62}, TorqueStructUnsafe_0{}}, TorqueStructfloat64_or_hole_0{TNode<BoolT>{tmp63}, TNode<Float64T>{tmp64}});
    ca_.Goto(&block53);
  }

  if (block63.is_used()) {
    ca_.Bind(&block63);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp65;
  TNode<FixedArrayBase> tmp66;
  TNode<FixedArray> tmp67;
  if (block52.is_used()) {
    ca_.Bind(&block52);
    tmp65 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp66 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp3, tmp65});
    compiler::CodeAssemblerLabel label68(&ca_);
    tmp67 = Cast_FixedArray_0(state_, TNode<HeapObject>{tmp66}, &label68);
    ca_.Goto(&block67);
    if (label68.is_used()) {
      ca_.Bind(&label68);
      ca_.Goto(&block68);
    }
  }

  if (block68.is_used()) {
    ca_.Bind(&block68);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp69;
  TNode<IntPtrT> tmp70;
  TNode<IntPtrT> tmp71;
  TNode<Smi> tmp72;
  TNode<IntPtrT> tmp73;
  TNode<IntPtrT> tmp74;
  TNode<UintPtrT> tmp75;
  TNode<UintPtrT> tmp76;
  TNode<BoolT> tmp77;
  if (block67.is_used()) {
    ca_.Bind(&block67);
    tmp69 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp70 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp71 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp72 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp67, tmp71});
    tmp73 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp72});
    tmp74 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp17});
    tmp75 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp74});
    tmp76 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp73});
    tmp77 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp75}, TNode<UintPtrT>{tmp76});
    ca_.Branch(tmp77, &block73, std::vector<Node*>{}, &block74, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp78;
  TNode<IntPtrT> tmp79;
  TNode<IntPtrT> tmp80;
  TNode<HeapObject> tmp81;
  TNode<IntPtrT> tmp82;
  TNode<Oddball> tmp83;
  if (block73.is_used()) {
    ca_.Bind(&block73);
    tmp78 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp79 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp74}, TNode<IntPtrT>{tmp78});
    tmp80 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp69}, TNode<IntPtrT>{tmp79});
    std::tie(tmp81, tmp82) = NewReference_Object_0(state_, TNode<HeapObject>{tmp67}, TNode<IntPtrT>{tmp80}).Flatten();
    tmp83 = TheHole_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp81, tmp82}, tmp83);
    ca_.Goto(&block53);
  }

  if (block74.is_used()) {
    ca_.Bind(&block74);
    CodeStubAssembler(state_).Unreachable();
  }

  if (block53.is_used()) {
    ca_.Bind(&block53);
    ca_.Goto(&block3, phi_bb15_13);
  }

  TNode<Object> phi_bb3_2;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_2);
    ca_.Goto(&block76, phi_bb3_2);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_Slow);
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    ca_.Goto(label_Runtime);
  }

  TNode<Object> phi_bb76_2;
    ca_.Bind(&block76, &phi_bb76_2);
  return TNode<Object>{phi_bb76_2};
}

TNode<Object> GenericArrayShift_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_receiver) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  TNode<Number> tmp1;
  TNode<Number> tmp2;
  TNode<BoolT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToObject_Inline(TNode<Context>{p_context}, TNode<Object>{p_receiver});
    tmp1 = GetLengthProperty_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp0});
    tmp2 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp3 = IsNumberEqual_0(state_, TNode<Number>{tmp1}, TNode<Number>{tmp2});
    ca_.Branch(tmp3, &block2, std::vector<Node*>{}, &block3, std::vector<Node*>{});
  }

  TNode<String> tmp4;
  TNode<Smi> tmp5;
  TNode<Object> tmp6;
  TNode<Oddball> tmp7;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp4 = kLengthString_0(state_);
    tmp5 = Convert_Smi_constexpr_int31_0(state_, 0);
    tmp6 = CodeStubAssembler(state_).CallBuiltin(Builtins::kSetProperty, p_context, tmp0, tmp4, tmp5);
    tmp7 = Undefined_0(state_);
    ca_.Goto(&block1, tmp7);
  }

  TNode<Smi> tmp8;
  TNode<Object> tmp9;
  TNode<Number> tmp10;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp8 = Convert_Smi_constexpr_int31_0(state_, 0);
    tmp9 = CodeStubAssembler(state_).GetProperty(TNode<Context>{p_context}, TNode<Object>{tmp0}, TNode<Object>{tmp8});
    tmp10 = FromConstexpr_Number_constexpr_int31_0(state_, 1);
    ca_.Goto(&block6, tmp10);
  }

  TNode<Number> phi_bb6_5;
  TNode<BoolT> tmp11;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_5);
    tmp11 = NumberIsLessThan_0(state_, TNode<Number>{phi_bb6_5}, TNode<Number>{tmp1});
    ca_.Branch(tmp11, &block4, std::vector<Node*>{phi_bb6_5}, &block5, std::vector<Node*>{phi_bb6_5});
  }

  TNode<Number> phi_bb4_5;
  TNode<Number> tmp12;
  TNode<Number> tmp13;
  TNode<Oddball> tmp14;
  TNode<Oddball> tmp15;
  TNode<BoolT> tmp16;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_5);
    tmp12 = FromConstexpr_Number_constexpr_int31_0(state_, 1);
    tmp13 = CodeStubAssembler(state_).NumberSub(TNode<Number>{phi_bb4_5}, TNode<Number>{tmp12});
    tmp14 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kHasProperty, p_context, tmp0, phi_bb4_5));
    tmp15 = True_0(state_);
    tmp16 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp14}, TNode<HeapObject>{tmp15});
    ca_.Branch(tmp16, &block7, std::vector<Node*>{phi_bb4_5, phi_bb4_5}, &block8, std::vector<Node*>{phi_bb4_5, phi_bb4_5});
  }

  TNode<Number> phi_bb7_5;
  TNode<Number> phi_bb7_6;
  TNode<Object> tmp17;
  TNode<Object> tmp18;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_5, &phi_bb7_6);
    tmp17 = CodeStubAssembler(state_).GetProperty(TNode<Context>{p_context}, TNode<Object>{tmp0}, TNode<Object>{phi_bb7_6});
    tmp18 = CodeStubAssembler(state_).CallBuiltin(Builtins::kSetProperty, p_context, tmp0, tmp13, tmp17);
    ca_.Goto(&block9, phi_bb7_5, phi_bb7_6);
  }

  TNode<Number> phi_bb8_5;
  TNode<Number> phi_bb8_6;
  TNode<Smi> tmp19;
  TNode<Oddball> tmp20;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_5, &phi_bb8_6);
    tmp19 = FromConstexpr_LanguageModeSmi_constexpr_LanguageMode_0(state_, LanguageMode::kStrict);
    tmp20 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kDeleteProperty, p_context, tmp0, tmp13, tmp19));
    ca_.Goto(&block9, phi_bb8_5, phi_bb8_6);
  }

  TNode<Number> phi_bb9_5;
  TNode<Number> phi_bb9_6;
  TNode<Number> tmp21;
  TNode<Number> tmp22;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_5, &phi_bb9_6);
    tmp21 = FromConstexpr_Number_constexpr_int31_0(state_, 1);
    tmp22 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{phi_bb9_5}, TNode<Number>{tmp21});
    ca_.Goto(&block6, tmp22);
  }

  TNode<Number> phi_bb5_5;
  TNode<Number> tmp23;
  TNode<Number> tmp24;
  TNode<Smi> tmp25;
  TNode<Oddball> tmp26;
  TNode<String> tmp27;
  TNode<Number> tmp28;
  TNode<Number> tmp29;
  TNode<Object> tmp30;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_5);
    tmp23 = FromConstexpr_Number_constexpr_int31_0(state_, 1);
    tmp24 = CodeStubAssembler(state_).NumberSub(TNode<Number>{tmp1}, TNode<Number>{tmp23});
    tmp25 = FromConstexpr_LanguageModeSmi_constexpr_LanguageMode_0(state_, LanguageMode::kStrict);
    tmp26 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kDeleteProperty, p_context, tmp0, tmp24, tmp25));
    tmp27 = kLengthString_0(state_);
    tmp28 = FromConstexpr_Number_constexpr_int31_0(state_, 1);
    tmp29 = CodeStubAssembler(state_).NumberSub(TNode<Number>{tmp1}, TNode<Number>{tmp28});
    tmp30 = CodeStubAssembler(state_).CallBuiltin(Builtins::kSetProperty, p_context, tmp0, tmp27, tmp29);
    ca_.Goto(&block1, tmp9);
  }

  TNode<Object> phi_bb1_2;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_2);
    ca_.Goto(&block10, phi_bb1_2);
  }

  TNode<Object> phi_bb10_2;
    ca_.Bind(&block10, &phi_bb10_2);
  return TNode<Object>{phi_bb10_2};
}

TF_BUILTIN(ArrayPrototypeShift, CodeStubAssembler) {
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
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Object> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    compiler::CodeAssemblerLabel label2(&ca_);
    tmp0 = TryFastArrayShift_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1, &label2);
    ca_.Goto(&block5);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block6);
    }
    if (label2.is_used()) {
      ca_.Bind(&label2);
      ca_.Goto(&block7);
    }
  }

  TNode<Object> tmp3;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp3 = GenericArrayShift_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    arguments.PopAndReturn(tmp3);
  }

  TNode<JSFunction> tmp4;
  TNode<Oddball> tmp5;
  TNode<Int32T> tmp6;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp4 = LoadTargetFromFrame_0(state_);
    tmp5 = Undefined_0(state_);
    tmp6 = Convert_int32_intptr_0(state_, TNode<IntPtrT>{torque_arguments.length});
   CodeStubAssembler(state_).TailCallBuiltin(Builtins::kArrayShift, parameter0, tmp4, tmp5, tmp6);
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    arguments.PopAndReturn(tmp0);
  }
}

}  // namespace internal
}  // namespace v8

