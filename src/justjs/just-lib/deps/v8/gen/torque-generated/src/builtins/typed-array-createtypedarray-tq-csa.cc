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

TNode<JSTypedArray> AllocateTypedArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, bool p_isOnHeap, TNode<Map> p_map, TNode<JSArrayBuffer> p_buffer, TNode<UintPtrT> p_byteOffset, TNode<UintPtrT> p_byteLength, TNode<UintPtrT> p_length) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<ByteArray> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    if ((p_isOnHeap)) {
      ca_.Goto(&block2);
    } else {
      ca_.Goto(&block3);
    }
  }

  TNode<ByteArray> tmp0;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp0 = CodeStubAssembler(state_).AllocateByteArray(TNode<UintPtrT>{p_byteLength});
    ca_.Goto(&block4, tmp0);
  }

  TNode<ByteArray> tmp1;
  TNode<RawPtrT> tmp2;
  TNode<UintPtrT> tmp3;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp1 = kEmptyByteArray_0(state_);
    tmp2 = CodeStubAssembler(state_).LoadJSArrayBufferBackingStorePtr(TNode<JSArrayBuffer>{p_buffer});
    tmp3 = Convert_uintptr_RawPtr_0(state_, TNode<RawPtrT>{tmp2});
    ca_.Goto(&block4, tmp1);
  }

  TNode<ByteArray> phi_bb4_6;
  TNode<JSObject> tmp4;
  TNode<JSTypedArray> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_6);
    tmp4 = AllocateFastOrSlowJSObjectFromMap_0(state_, TNode<Context>{p_context}, TNode<Map>{p_map});
    tmp5 = UnsafeCast_JSTypedArray_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp4});
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    CodeStubAssembler(state_).StoreReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp5, tmp6}, phi_bb4_6);
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    CodeStubAssembler(state_).StoreReference<JSArrayBuffer>(CodeStubAssembler::Reference{tmp5, tmp7}, p_buffer);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    CodeStubAssembler(state_).StoreReference<UintPtrT>(CodeStubAssembler::Reference{tmp5, tmp8}, p_byteOffset);
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    CodeStubAssembler(state_).StoreReference<UintPtrT>(CodeStubAssembler::Reference{tmp5, tmp9}, p_byteLength);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    CodeStubAssembler(state_).StoreReference<UintPtrT>(CodeStubAssembler::Reference{tmp5, tmp10}, p_length);
    if ((p_isOnHeap)) {
      ca_.Goto(&block12);
    } else {
      ca_.Goto(&block13);
    }
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    TypedArrayBuiltinsAssembler(state_).SetJSTypedArrayOnHeapDataPtr(TNode<JSTypedArray>{tmp5}, TNode<ByteArray>{phi_bb4_6}, TNode<UintPtrT>{p_byteOffset});
    ca_.Goto(&block14);
  }

  TNode<RawPtrT> tmp11;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp11 = CodeStubAssembler(state_).LoadJSArrayBufferBackingStorePtr(TNode<JSArrayBuffer>{p_buffer});
    TypedArrayBuiltinsAssembler(state_).SetJSTypedArrayOffHeapDataPtr(TNode<JSTypedArray>{tmp5}, TNode<RawPtrT>{tmp11}, TNode<UintPtrT>{p_byteOffset});
    ca_.Goto(&block14);
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    TypedArrayBuiltinsAssembler(state_).SetupTypedArrayEmbedderFields(TNode<JSTypedArray>{tmp5});
    ca_.Goto(&block19);
  }

    ca_.Bind(&block19);
  return TNode<JSTypedArray>{tmp5};
}

TNode<JSTypedArray> TypedArrayInitialize_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, bool p_initialize, TNode<Map> p_map, TNode<UintPtrT> p_length, TorqueStructTypedArrayElementsInfo p_elementsInfo, TNode<JSReceiver> p_bufferConstructor, compiler::CodeAssemblerLabel* label_IfRangeError) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object, Object> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object, Object> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSTypedArray> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSTypedArray> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<UintPtrT> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_uintptr_constexpr_uintptr_0(state_, JSTypedArray::kMaxLength);
    tmp1 = CodeStubAssembler(state_).UintPtrGreaterThan(TNode<UintPtrT>{p_length}, TNode<UintPtrT>{tmp0});
    ca_.Branch(tmp1, &block4, std::vector<Node*>{}, &block5, std::vector<Node*>{});
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    ca_.Goto(&block1);
  }

  TNode<UintPtrT> tmp2;
  TNode<UintPtrT> tmp3;
  TNode<BoolT> tmp4;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp2 = FromConstexpr_uintptr_constexpr_uintptr_0(state_, JSArrayBuffer::kMaxByteLength);
    tmp3 = CodeStubAssembler(state_).WordShr(TNode<UintPtrT>{tmp2}, TNode<UintPtrT>{p_elementsInfo.sizeLog2});
    tmp4 = CodeStubAssembler(state_).UintPtrGreaterThan(TNode<UintPtrT>{p_length}, TNode<UintPtrT>{tmp3});
    ca_.Branch(tmp4, &block6, std::vector<Node*>{}, &block7, std::vector<Node*>{});
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block1);
  }

  TNode<UintPtrT> tmp5;
  TNode<Number> tmp6;
  TNode<JSReceiver> tmp7;
  TNode<UintPtrT> tmp8;
  TNode<BoolT> tmp9;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp5 = CodeStubAssembler(state_).WordShl(TNode<UintPtrT>{p_length}, TNode<UintPtrT>{p_elementsInfo.sizeLog2});
    tmp6 = Convert_Number_uintptr_0(state_, TNode<UintPtrT>{tmp5});
    tmp7 = GetArrayBufferFunction_0(state_, TNode<Context>{p_context});
    tmp8 = FromConstexpr_uintptr_constexpr_int31_0(state_, 0);
    tmp9 = CodeStubAssembler(state_).TaggedNotEqual(TNode<HeapObject>{p_bufferConstructor}, TNode<HeapObject>{tmp7});
    ca_.Branch(tmp9, &block12, std::vector<Node*>{}, &block13, std::vector<Node*>{});
  }

  TNode<JSReceiver> tmp10;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp10 = CodeStubAssembler(state_).ConstructWithTarget(TNode<Context>{p_context}, TNode<JSReceiver>{tmp7}, TNode<JSReceiver>{p_bufferConstructor}, TNode<Object>{tmp6});
    ca_.Goto(&block9, tmp10);
  }

  TNode<UintPtrT> tmp11;
  TNode<BoolT> tmp12;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp11 = FromConstexpr_uintptr_constexpr_int31_0(state_, JSTypedArray::kMaxSizeInHeap);
    tmp12 = CodeStubAssembler(state_).UintPtrGreaterThan(TNode<UintPtrT>{tmp5}, TNode<UintPtrT>{tmp11});
    ca_.Branch(tmp12, &block14, std::vector<Node*>{}, &block15, std::vector<Node*>{});
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    if ((p_initialize)) {
      ca_.Goto(&block19);
    } else {
      ca_.Goto(&block20);
    }
  }

  TNode<JSArrayBuffer> tmp13;
  TNode<JSTypedArray> tmp14;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp13 = TypedArrayBuiltinsAssembler(state_).AllocateEmptyOnHeapBuffer(TNode<Context>{p_context}, TNode<UintPtrT>{tmp5});
    tmp14 = AllocateTypedArray_0(state_, TNode<Context>{p_context}, true, TNode<Map>{p_map}, TNode<JSArrayBuffer>{tmp13}, TNode<UintPtrT>{tmp8}, TNode<UintPtrT>{tmp5}, TNode<UintPtrT>{p_length});
    if ((p_initialize)) {
      ca_.Goto(&block16);
    } else {
      ca_.Goto(&block17);
    }
  }

  TNode<RawPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp15 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{tmp14});
    tmp16 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    TypedArrayBuiltinsAssembler(state_).CallCMemset(TNode<RawPtrT>{tmp15}, TNode<IntPtrT>{tmp16}, TNode<UintPtrT>{tmp5});
    ca_.Goto(&block18);
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    ca_.Goto(&block18);
  }

  if (block18.is_used()) {
    ca_.Bind(&block18);
    ca_.Goto(&block2, tmp14);
  }

  TNode<JSReceiver> tmp17;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp17 = CodeStubAssembler(state_).Construct(TNode<Context>{p_context}, TNode<JSReceiver>{tmp7}, TNode<Object>{tmp6});
    ca_.Goto(&block9, tmp17);
  }

  TNode<JSFunction> tmp18;
  TNode<Oddball> tmp19;
  TNode<Object> tmp20;
  if (block20.is_used()) {
    ca_.Bind(&block20);
    tmp18 = GetArrayBufferNoInitFunction_0(state_, TNode<Context>{p_context});
    tmp19 = Undefined_0(state_);
    tmp20 = CodeStubAssembler(state_).Call(TNode<Context>{p_context}, TNode<Object>{tmp18}, TNode<Object>{tmp19}, TNode<Object>{tmp6});
    ca_.Goto(&block9, tmp20);
  }

  TNode<Object> phi_bb9_10;
  TNode<JSArrayBuffer> tmp21;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_10);
    compiler::CodeAssemblerLabel label22(&ca_);
    tmp21 = Cast_JSArrayBuffer_1(state_, TNode<Context>{p_context}, TNode<Object>{phi_bb9_10}, &label22);
    ca_.Goto(&block24, phi_bb9_10, phi_bb9_10);
    if (label22.is_used()) {
      ca_.Bind(&label22);
      ca_.Goto(&block25, phi_bb9_10, phi_bb9_10);
    }
  }

  TNode<Object> phi_bb25_10;
  TNode<Object> phi_bb25_11;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_10, &phi_bb25_11);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Object> phi_bb24_10;
  TNode<Object> phi_bb24_11;
  TNode<JSTypedArray> tmp23;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_10, &phi_bb24_11);
    tmp23 = AllocateTypedArray_0(state_, TNode<Context>{p_context}, false, TNode<Map>{p_map}, TNode<JSArrayBuffer>{tmp21}, TNode<UintPtrT>{tmp8}, TNode<UintPtrT>{tmp5}, TNode<UintPtrT>{p_length});
    ca_.Goto(&block2, tmp23);
  }

  TNode<JSTypedArray> phi_bb2_6;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_6);
    ca_.Goto(&block26, phi_bb2_6);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_IfRangeError);
  }

  TNode<JSTypedArray> phi_bb26_6;
    ca_.Bind(&block26, &phi_bb26_6);
  return TNode<JSTypedArray>{phi_bb26_6};
}

TNode<JSTypedArray> ConstructByLength_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Map> p_map, TNode<Object> p_lengthObj, TorqueStructTypedArrayElementsInfo p_elementsInfo) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<UintPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = ToIndex_0(state_, TNode<Context>{p_context}, TNode<Object>{p_lengthObj}, &label1);
    ca_.Goto(&block4);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block5);
    }
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    ca_.Goto(&block3);
  }

  TNode<JSReceiver> tmp2;
  TNode<JSTypedArray> tmp3;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp2 = GetArrayBufferFunction_0(state_, TNode<Context>{p_context});
    compiler::CodeAssemblerLabel label4(&ca_);
    tmp3 = TypedArrayInitialize_0(state_, TNode<Context>{p_context}, true, TNode<Map>{p_map}, TNode<UintPtrT>{tmp0}, TorqueStructTypedArrayElementsInfo{TNode<UintPtrT>{p_elementsInfo.sizeLog2}, TNode<Int32T>{p_elementsInfo.kind}}, TNode<JSReceiver>{tmp2}, &label4);
    ca_.Goto(&block6);
    if (label4.is_used()) {
      ca_.Bind(&label4);
      ca_.Goto(&block7);
    }
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    ca_.Goto(&block3);
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block8);
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    CodeStubAssembler(state_).ThrowRangeError(TNode<Context>{p_context}, MessageTemplate::kInvalidTypedArrayLength, TNode<Object>{p_lengthObj});
  }

    ca_.Bind(&block8);
  return TNode<JSTypedArray>{tmp3};
}

TNode<JSTypedArray> ConstructByArrayLike_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Map> p_map, TNode<HeapObject> p_arrayLike, TNode<UintPtrT> p_length, TorqueStructTypedArrayElementsInfo p_elementsInfo, TNode<JSReceiver> p_bufferConstructor) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSTypedArray> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = TypedArrayInitialize_0(state_, TNode<Context>{p_context}, false, TNode<Map>{p_map}, TNode<UintPtrT>{p_length}, TorqueStructTypedArrayElementsInfo{TNode<UintPtrT>{p_elementsInfo.sizeLog2}, TNode<Int32T>{p_elementsInfo.kind}}, TNode<JSReceiver>{p_bufferConstructor}, &label1);
    ca_.Goto(&block4);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block5);
    }
  }

  TNode<Number> tmp2;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp2 = Convert_Number_uintptr_0(state_, TNode<UintPtrT>{p_length});
    CodeStubAssembler(state_).ThrowRangeError(TNode<Context>{p_context}, MessageTemplate::kInvalidTypedArrayLength, TNode<Object>{tmp2});
  }

  TNode<JSTypedArray> tmp3;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    compiler::CodeAssemblerLabel label4(&ca_);
    tmp3 = Cast_JSTypedArray_0(state_, TNode<HeapObject>{p_arrayLike}, &label4);
    ca_.Goto(&block8);
    if (label4.is_used()) {
      ca_.Bind(&label4);
      ca_.Goto(&block9);
    }
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    ca_.Goto(&block7);
  }

  TNode<IntPtrT> tmp5;
  TNode<JSArrayBuffer> tmp6;
  TNode<BoolT> tmp7;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp5 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp6 = CodeStubAssembler(state_).LoadReference<JSArrayBuffer>(CodeStubAssembler::Reference{tmp3, tmp5});
    tmp7 = IsDetachedBuffer_0(state_, TNode<JSArrayBuffer>{tmp6});
    ca_.Branch(tmp7, &block10, std::vector<Node*>{}, &block11, std::vector<Node*>{});
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{p_context}, MessageTemplate::kDetachedOperation, "Construct");
  }

  TNode<Int32T> tmp8;
  TNode<BoolT> tmp9;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp8 = CodeStubAssembler(state_).LoadElementsKind(TNode<JSTypedArray>{tmp3});
    tmp9 = ElementsKindNotEqual_0(state_, TNode<Int32T>{tmp8}, TNode<Int32T>{p_elementsInfo.kind});
    ca_.Branch(tmp9, &block13, std::vector<Node*>{}, &block14, std::vector<Node*>{});
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    ca_.Goto(&block7);
  }

  TNode<UintPtrT> tmp10;
  TNode<BoolT> tmp11;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp10 = FromConstexpr_uintptr_constexpr_int31_0(state_, 0);
    tmp11 = CodeStubAssembler(state_).UintPtrGreaterThan(TNode<UintPtrT>{p_length}, TNode<UintPtrT>{tmp10});
    ca_.Branch(tmp11, &block16, std::vector<Node*>{}, &block17, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp12;
  TNode<UintPtrT> tmp13;
  TNode<RawPtrT> tmp14;
  TNode<RawPtrT> tmp15;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    tmp13 = CodeStubAssembler(state_).LoadReference<UintPtrT>(CodeStubAssembler::Reference{tmp0, tmp12});
    tmp14 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{tmp0});
    tmp15 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{tmp3});
    TypedArrayBuiltinsAssembler(state_).CallCMemcpy(TNode<RawPtrT>{tmp14}, TNode<RawPtrT>{tmp15}, TNode<UintPtrT>{tmp13});
    ca_.Goto(&block17);
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    ca_.Goto(&block6);
  }

  TNode<UintPtrT> tmp16;
  TNode<BoolT> tmp17;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp16 = FromConstexpr_uintptr_constexpr_int31_0(state_, 0);
    tmp17 = CodeStubAssembler(state_).UintPtrGreaterThan(TNode<UintPtrT>{p_length}, TNode<UintPtrT>{tmp16});
    ca_.Branch(tmp17, &block22, std::vector<Node*>{}, &block23, std::vector<Node*>{});
  }

  TNode<Number> tmp18;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    tmp18 = Convert_Number_uintptr_0(state_, TNode<UintPtrT>{p_length});
    CodeStubAssembler(state_).CallRuntime(Runtime::kTypedArrayCopyElements, p_context, tmp0, p_arrayLike, tmp18);
    ca_.Goto(&block23);
  }

  if (block23.is_used()) {
    ca_.Bind(&block23);
    ca_.Goto(&block6);
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block24);
  }

    ca_.Bind(&block24);
  return TNode<JSTypedArray>{tmp0};
}

void ConstructByIterable_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_iterable, TNode<JSReceiver> p_iteratorFn, compiler::CodeAssemblerLabel* label_IfConstructByArrayLike, compiler::TypedCodeAssemblerVariable<JSArray>* label_IfConstructByArrayLike_parameter_0, compiler::TypedCodeAssemblerVariable<UintPtrT>* label_IfConstructByArrayLike_parameter_1, compiler::TypedCodeAssemblerVariable<JSReceiver>* label_IfConstructByArrayLike_parameter_2) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSArray> tmp0;
  TNode<UintPtrT> tmp1;
  TNode<JSReceiver> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kIterableToListMayPreserveHoles, p_context, p_iterable, p_iteratorFn));
    tmp1 = LoadJSArrayLengthAsUintPtr_0(state_, TNode<JSArray>{tmp0});
    tmp2 = GetArrayBufferFunction_0(state_, TNode<Context>{p_context});
    *label_IfConstructByArrayLike_parameter_2 = tmp2;
    *label_IfConstructByArrayLike_parameter_1 = tmp1;
    *label_IfConstructByArrayLike_parameter_0 = tmp0;
    ca_.Goto(label_IfConstructByArrayLike);
  }
}

void ConstructByTypedArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSTypedArray> p_srcTypedArray, compiler::CodeAssemblerLabel* label_IfConstructByArrayLike, compiler::TypedCodeAssemblerVariable<JSTypedArray>* label_IfConstructByArrayLike_parameter_0, compiler::TypedCodeAssemblerVariable<UintPtrT>* label_IfConstructByArrayLike_parameter_1, compiler::TypedCodeAssemblerVariable<JSReceiver>* label_IfConstructByArrayLike_parameter_2) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSReceiver, UintPtrT> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<JSArrayBuffer> tmp2;
  TNode<BoolT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = GetArrayBufferFunction_0(state_, TNode<Context>{p_context});
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp2 = CodeStubAssembler(state_).LoadReference<JSArrayBuffer>(CodeStubAssembler::Reference{p_srcTypedArray, tmp1});
    tmp3 = IsDetachedBuffer_0(state_, TNode<JSArrayBuffer>{tmp2});
    ca_.Branch(tmp3, &block2, std::vector<Node*>{}, &block3, std::vector<Node*>{});
  }

  TNode<UintPtrT> tmp4;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp4 = FromConstexpr_uintptr_constexpr_int31_0(state_, 0);
    ca_.Goto(&block4, tmp4);
  }

  TNode<IntPtrT> tmp5;
  TNode<UintPtrT> tmp6;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp5 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp6 = CodeStubAssembler(state_).LoadReference<UintPtrT>(CodeStubAssembler::Reference{p_srcTypedArray, tmp5});
    ca_.Goto(&block4, tmp6);
  }

  TNode<UintPtrT> phi_bb4_4;
  TNode<BoolT> tmp7;
  TNode<BoolT> tmp8;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_4);
    tmp7 = IsSharedArrayBuffer_0(state_, TNode<JSArrayBuffer>{tmp2});
    tmp8 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp7});
    ca_.Branch(tmp8, &block6, std::vector<Node*>{}, &block7, std::vector<Node*>{tmp0, phi_bb4_4});
  }

  TNode<JSReceiver> tmp9;
  TNode<BoolT> tmp10;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp9 = CodeStubAssembler(state_).SpeciesConstructor(TNode<Context>{p_context}, TNode<Object>{tmp2}, TNode<JSReceiver>{tmp0});
    tmp10 = IsDetachedBuffer_0(state_, TNode<JSArrayBuffer>{tmp2});
    ca_.Branch(tmp10, &block8, std::vector<Node*>{}, &block9, std::vector<Node*>{phi_bb4_4});
  }

  TNode<UintPtrT> tmp11;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp11 = FromConstexpr_uintptr_constexpr_int31_0(state_, 0);
    ca_.Goto(&block9, tmp11);
  }

  TNode<UintPtrT> phi_bb9_4;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_4);
    ca_.Goto(&block7, tmp9, phi_bb9_4);
  }

  TNode<JSReceiver> phi_bb7_2;
  TNode<UintPtrT> phi_bb7_4;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_2, &phi_bb7_4);
    *label_IfConstructByArrayLike_parameter_2 = phi_bb7_2;
    *label_IfConstructByArrayLike_parameter_1 = phi_bb7_4;
    *label_IfConstructByArrayLike_parameter_0 = p_srcTypedArray;
    ca_.Goto(label_IfConstructByArrayLike);
  }
}

TNode<JSTypedArray> ConstructByArrayBuffer_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Map> p_map, TNode<JSArrayBuffer> p_buffer, TNode<Object> p_byteOffset, TNode<Object> p_length, TorqueStructTypedArrayElementsInfo p_elementsInfo) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String> block7(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<UintPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = ToIndex_0(state_, TNode<Context>{p_context}, TNode<Object>{p_byteOffset}, &label1);
    ca_.Goto(&block8);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block9);
    }
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    ca_.Goto(&block3);
  }

  TNode<UintPtrT> tmp2;
  TNode<UintPtrT> tmp3;
  TNode<UintPtrT> tmp4;
  TNode<UintPtrT> tmp5;
  TNode<UintPtrT> tmp6;
  TNode<UintPtrT> tmp7;
  TNode<BoolT> tmp8;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp2 = FromConstexpr_uintptr_constexpr_int31_0(state_, 1);
    tmp3 = CodeStubAssembler(state_).WordShl(TNode<UintPtrT>{tmp2}, TNode<UintPtrT>{p_elementsInfo.sizeLog2});
    tmp4 = FromConstexpr_uintptr_constexpr_int31_0(state_, 1);
    tmp5 = CodeStubAssembler(state_).UintPtrSub(TNode<UintPtrT>{tmp3}, TNode<UintPtrT>{tmp4});
    tmp6 = CodeStubAssembler(state_).WordAnd(TNode<UintPtrT>{tmp0}, TNode<UintPtrT>{tmp5});
    tmp7 = FromConstexpr_uintptr_constexpr_int31_0(state_, 0);
    tmp8 = CodeStubAssembler(state_).WordNotEqual(TNode<UintPtrT>{tmp6}, TNode<UintPtrT>{tmp7});
    ca_.Branch(tmp8, &block10, std::vector<Node*>{}, &block11, std::vector<Node*>{});
  }

  TNode<String> tmp9;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp9 = FromConstexpr_String_constexpr_string_0(state_, "start offset");
    ca_.Goto(&block7, tmp9);
  }

  TNode<UintPtrT> tmp10;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    compiler::CodeAssemblerLabel label11(&ca_);
    tmp10 = ToIndex_0(state_, TNode<Context>{p_context}, TNode<Object>{p_length}, &label11);
    ca_.Goto(&block13);
    if (label11.is_used()) {
      ca_.Bind(&label11);
      ca_.Goto(&block14);
    }
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    ca_.Goto(&block5);
  }

  TNode<BoolT> tmp12;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp12 = IsDetachedBuffer_0(state_, TNode<JSArrayBuffer>{p_buffer});
    ca_.Branch(tmp12, &block15, std::vector<Node*>{}, &block16, std::vector<Node*>{});
  }

  if (block15.is_used()) {
    ca_.Bind(&block15);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{p_context}, MessageTemplate::kDetachedOperation, "Construct");
  }

  TNode<IntPtrT> tmp13;
  TNode<UintPtrT> tmp14;
  TNode<Oddball> tmp15;
  TNode<BoolT> tmp16;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp13 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp14 = CodeStubAssembler(state_).LoadReference<UintPtrT>(CodeStubAssembler::Reference{p_buffer, tmp13});
    tmp15 = Undefined_0(state_);
    tmp16 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{p_length}, TNode<HeapObject>{tmp15});
    ca_.Branch(tmp16, &block17, std::vector<Node*>{}, &block18, std::vector<Node*>{});
  }

  TNode<UintPtrT> tmp17;
  TNode<UintPtrT> tmp18;
  TNode<UintPtrT> tmp19;
  TNode<UintPtrT> tmp20;
  TNode<UintPtrT> tmp21;
  TNode<UintPtrT> tmp22;
  TNode<BoolT> tmp23;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp17 = FromConstexpr_uintptr_constexpr_int31_0(state_, 1);
    tmp18 = CodeStubAssembler(state_).WordShl(TNode<UintPtrT>{tmp17}, TNode<UintPtrT>{p_elementsInfo.sizeLog2});
    tmp19 = FromConstexpr_uintptr_constexpr_int31_0(state_, 1);
    tmp20 = CodeStubAssembler(state_).UintPtrSub(TNode<UintPtrT>{tmp18}, TNode<UintPtrT>{tmp19});
    tmp21 = CodeStubAssembler(state_).WordAnd(TNode<UintPtrT>{tmp14}, TNode<UintPtrT>{tmp20});
    tmp22 = FromConstexpr_uintptr_constexpr_int31_0(state_, 0);
    tmp23 = CodeStubAssembler(state_).WordNotEqual(TNode<UintPtrT>{tmp21}, TNode<UintPtrT>{tmp22});
    ca_.Branch(tmp23, &block20, std::vector<Node*>{}, &block21, std::vector<Node*>{});
  }

  TNode<String> tmp24;
  if (block20.is_used()) {
    ca_.Bind(&block20);
    tmp24 = FromConstexpr_String_constexpr_string_0(state_, "byte length");
    ca_.Goto(&block7, tmp24);
  }

  TNode<BoolT> tmp25;
  if (block21.is_used()) {
    ca_.Bind(&block21);
    tmp25 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp14}, TNode<UintPtrT>{tmp0});
    ca_.Branch(tmp25, &block23, std::vector<Node*>{}, &block24, std::vector<Node*>{});
  }

  if (block23.is_used()) {
    ca_.Bind(&block23);
    ca_.Goto(&block3);
  }

  TNode<UintPtrT> tmp26;
  TNode<UintPtrT> tmp27;
  TNode<UintPtrT> tmp28;
  TNode<BoolT> tmp29;
  if (block24.is_used()) {
    ca_.Bind(&block24);
    tmp26 = CodeStubAssembler(state_).UintPtrSub(TNode<UintPtrT>{tmp14}, TNode<UintPtrT>{tmp0});
    tmp27 = CodeStubAssembler(state_).WordShr(TNode<UintPtrT>{tmp26}, TNode<UintPtrT>{p_elementsInfo.sizeLog2});
    tmp28 = FromConstexpr_uintptr_constexpr_uintptr_0(state_, JSTypedArray::kMaxLength);
    tmp29 = CodeStubAssembler(state_).UintPtrGreaterThan(TNode<UintPtrT>{tmp27}, TNode<UintPtrT>{tmp28});
    ca_.Branch(tmp29, &block26, std::vector<Node*>{}, &block27, std::vector<Node*>{});
  }

  if (block26.is_used()) {
    ca_.Bind(&block26);
    ca_.Goto(&block3);
  }

  if (block27.is_used()) {
    ca_.Bind(&block27);
    ca_.Goto(&block19, tmp27, tmp26);
  }

  TNode<UintPtrT> tmp30;
  TNode<BoolT> tmp31;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp30 = FromConstexpr_uintptr_constexpr_uintptr_0(state_, JSTypedArray::kMaxLength);
    tmp31 = CodeStubAssembler(state_).UintPtrGreaterThan(TNode<UintPtrT>{tmp10}, TNode<UintPtrT>{tmp30});
    ca_.Branch(tmp31, &block29, std::vector<Node*>{}, &block30, std::vector<Node*>{});
  }

  if (block29.is_used()) {
    ca_.Bind(&block29);
    ca_.Goto(&block5);
  }

  TNode<UintPtrT> tmp32;
  TNode<UintPtrT> tmp33;
  TNode<BoolT> tmp34;
  if (block30.is_used()) {
    ca_.Bind(&block30);
    tmp32 = FromConstexpr_uintptr_constexpr_uintptr_0(state_, JSArrayBuffer::kMaxByteLength);
    tmp33 = CodeStubAssembler(state_).WordShr(TNode<UintPtrT>{tmp32}, TNode<UintPtrT>{p_elementsInfo.sizeLog2});
    tmp34 = CodeStubAssembler(state_).UintPtrGreaterThan(TNode<UintPtrT>{tmp10}, TNode<UintPtrT>{tmp33});
    ca_.Branch(tmp34, &block31, std::vector<Node*>{}, &block32, std::vector<Node*>{});
  }

  if (block31.is_used()) {
    ca_.Bind(&block31);
    ca_.Goto(&block5);
  }

  TNode<UintPtrT> tmp35;
  TNode<BoolT> tmp36;
  if (block32.is_used()) {
    ca_.Bind(&block32);
    tmp35 = CodeStubAssembler(state_).WordShl(TNode<UintPtrT>{tmp10}, TNode<UintPtrT>{p_elementsInfo.sizeLog2});
    tmp36 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp14}, TNode<UintPtrT>{tmp35});
    ca_.Branch(tmp36, &block35, std::vector<Node*>{}, &block36, std::vector<Node*>{});
  }

  TNode<BoolT> tmp37;
  if (block35.is_used()) {
    ca_.Bind(&block35);
    tmp37 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block37, tmp37);
  }

  TNode<UintPtrT> tmp38;
  TNode<BoolT> tmp39;
  if (block36.is_used()) {
    ca_.Bind(&block36);
    tmp38 = CodeStubAssembler(state_).UintPtrSub(TNode<UintPtrT>{tmp14}, TNode<UintPtrT>{tmp35});
    tmp39 = CodeStubAssembler(state_).UintPtrGreaterThan(TNode<UintPtrT>{tmp0}, TNode<UintPtrT>{tmp38});
    ca_.Goto(&block37, tmp39);
  }

  TNode<BoolT> phi_bb37_12;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_12);
    ca_.Branch(phi_bb37_12, &block33, std::vector<Node*>{}, &block34, std::vector<Node*>{});
  }

  if (block33.is_used()) {
    ca_.Bind(&block33);
    ca_.Goto(&block5);
  }

  if (block34.is_used()) {
    ca_.Bind(&block34);
    ca_.Goto(&block19, tmp10, tmp35);
  }

  TNode<UintPtrT> phi_bb19_8;
  TNode<UintPtrT> phi_bb19_9;
  TNode<JSTypedArray> tmp40;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_8, &phi_bb19_9);
    tmp40 = AllocateTypedArray_0(state_, TNode<Context>{p_context}, false, TNode<Map>{p_map}, TNode<JSArrayBuffer>{p_buffer}, TNode<UintPtrT>{tmp0}, TNode<UintPtrT>{phi_bb19_9}, TNode<UintPtrT>{phi_bb19_8});
    ca_.Goto(&block38);
  }

  TNode<String> phi_bb7_7;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_7);
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowInvalidTypedArrayAlignment, p_context, p_map, phi_bb7_7);
    CodeStubAssembler(state_).Unreachable();
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    CodeStubAssembler(state_).ThrowRangeError(TNode<Context>{p_context}, MessageTemplate::kInvalidTypedArrayLength, TNode<Object>{p_length});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    CodeStubAssembler(state_).ThrowRangeError(TNode<Context>{p_context}, MessageTemplate::kInvalidOffset, TNode<Object>{p_byteOffset});
  }

    ca_.Bind(&block38);
  return TNode<JSTypedArray>{tmp40};
}

TNode<JSTypedArray> TypedArrayCreateByLength_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_constructor, TNode<Number> p_length, const char* p_methodName) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  TNode<JSTypedArray> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<JSArrayBuffer> tmp3;
  TNode<BoolT> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).Construct(TNode<Context>{p_context}, TNode<JSReceiver>{p_constructor}, TNode<Object>{p_length});
    tmp1 = TypedArrayBuiltinsAssembler(state_).ValidateTypedArray(TNode<Context>{p_context}, TNode<Object>{tmp0}, p_methodName);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp3 = CodeStubAssembler(state_).LoadReference<JSArrayBuffer>(CodeStubAssembler::Reference{tmp1, tmp2});
    tmp4 = IsDetachedBuffer_0(state_, TNode<JSArrayBuffer>{tmp3});
    ca_.Branch(tmp4, &block6, std::vector<Node*>{}, &block7, std::vector<Node*>{});
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{p_context}, MessageTemplate::kDetachedOperation, p_methodName);
  }

  TNode<IntPtrT> tmp5;
  TNode<UintPtrT> tmp6;
  TNode<UintPtrT> tmp7;
  TNode<BoolT> tmp8;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp5 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp6 = CodeStubAssembler(state_).LoadReference<UintPtrT>(CodeStubAssembler::Reference{tmp1, tmp5});
    tmp7 = Convert_uintptr_Number_0(state_, TNode<Number>{p_length});
    tmp8 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp6}, TNode<UintPtrT>{tmp7});
    ca_.Branch(tmp8, &block8, std::vector<Node*>{}, &block9, std::vector<Node*>{});
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{p_context}, MessageTemplate::kTypedArrayTooShort);
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    ca_.Goto(&block10);
  }

    ca_.Bind(&block10);
  return TNode<JSTypedArray>{tmp1};
}

void ConstructByJSReceiver_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_obj, compiler::CodeAssemblerLabel* label_IfConstructByArrayLike, compiler::TypedCodeAssemblerVariable<JSReceiver>* label_IfConstructByArrayLike_parameter_0, compiler::TypedCodeAssemblerVariable<UintPtrT>* label_IfConstructByArrayLike_parameter_1, compiler::TypedCodeAssemblerVariable<JSReceiver>* label_IfConstructByArrayLike_parameter_2) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSReceiver, UintPtrT, JSReceiver> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Symbol> tmp0;
  TNode<JSReceiver> tmp1;
    compiler::TypedCodeAssemblerVariable<Object> tmp4(&ca_);
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).IteratorSymbolConstant();
    compiler::CodeAssemblerLabel label2(&ca_);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp1 = GetMethod_0(state_, TNode<Context>{p_context}, TNode<Object>{p_obj}, TNode<Name>{tmp0}, &label2, &label3, &tmp4);
    ca_.Goto(&block8);
    if (label2.is_used()) {
      ca_.Bind(&label2);
      ca_.Goto(&block9);
    }
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block10);
    }
  }

  TNode<String> tmp5;
  TNode<Object> tmp6;
  TNode<Number> tmp7;
  TNode<UintPtrT> tmp8;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp5 = kLengthString_0(state_);
    tmp6 = CodeStubAssembler(state_).GetProperty(TNode<Context>{p_context}, TNode<Object>{p_obj}, TNode<Object>{tmp5});
    tmp7 = CodeStubAssembler(state_).ToLength_Inline(TNode<Context>{p_context}, TNode<Object>{tmp6});
    compiler::CodeAssemblerLabel label9(&ca_);
    tmp8 = ChangeSafeIntegerNumberToUintPtr_0(state_, TNode<Number>{tmp7}, &label9);
    ca_.Goto(&block14);
    if (label9.is_used()) {
      ca_.Bind(&label9);
      ca_.Goto(&block15);
    }
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{p_context}, MessageTemplate::kIteratorSymbolNonCallable);
  }

    compiler::TypedCodeAssemblerVariable<JSArray> tmp11(&ca_);
    compiler::TypedCodeAssemblerVariable<UintPtrT> tmp12(&ca_);
    compiler::TypedCodeAssemblerVariable<JSReceiver> tmp13(&ca_);
  if (block8.is_used()) {
    ca_.Bind(&block8);
    compiler::CodeAssemblerLabel label10(&ca_);
    ConstructByIterable_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{p_obj}, TNode<JSReceiver>{tmp1}, &label10, &tmp11, &tmp12, &tmp13);
    if (label10.is_used()) {
      ca_.Bind(&label10);
      ca_.Goto(&block11);
    }
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    ca_.Goto(&block1, tmp11.value(), tmp12.value(), tmp13.value());
  }

  if (block15.is_used()) {
    ca_.Bind(&block15);
    CodeStubAssembler(state_).ThrowRangeError(TNode<Context>{p_context}, MessageTemplate::kInvalidTypedArrayLength, TNode<Object>{tmp7});
  }

  TNode<JSReceiver> tmp14;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp14 = GetArrayBufferFunction_0(state_, TNode<Context>{p_context});
    ca_.Goto(&block1, p_obj, tmp8, tmp14);
  }

  TNode<JSReceiver> phi_bb1_0;
  TNode<UintPtrT> phi_bb1_1;
  TNode<JSReceiver> phi_bb1_2;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_0, &phi_bb1_1, &phi_bb1_2);
    *label_IfConstructByArrayLike_parameter_2 = phi_bb1_2;
    *label_IfConstructByArrayLike_parameter_1 = phi_bb1_1;
    *label_IfConstructByArrayLike_parameter_0 = phi_bb1_0;
    ca_.Goto(label_IfConstructByArrayLike);
  }
}

TF_BUILTIN(CreateTypedArray, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSFunction> parameter1 = UncheckedCast<JSFunction>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<JSReceiver> parameter2 = UncheckedCast<JSReceiver>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  TNode<Object> parameter4 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<3>()));
  USE(parameter4);
  TNode<Object> parameter5 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<4>()));
  USE(parameter5);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSReceiver, UintPtrT, JSReceiver> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Map> tmp0;
  TNode<UintPtrT> tmp1;
  TNode<Int32T> tmp2;
  TNode<Smi> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = GetDerivedMap_0(state_, TNode<Context>{parameter0}, TNode<JSFunction>{parameter1}, TNode<JSReceiver>{parameter2});
    std::tie(tmp1, tmp2) = TypedArrayBuiltinsAssembler(state_).GetTypedArrayElementsInfo(TNode<Map>{tmp0}).Flatten();
    compiler::CodeAssemblerLabel label4(&ca_);
    tmp3 = Cast_Smi_0(state_, TNode<Object>{parameter3}, &label4);
    ca_.Goto(&block11);
    if (label4.is_used()) {
      ca_.Bind(&label4);
      ca_.Goto(&block12);
    }
  }

  TNode<JSArrayBuffer> tmp5;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    compiler::CodeAssemblerLabel label6(&ca_);
    tmp5 = Cast_JSArrayBuffer_0(state_, TNode<HeapObject>{ca_.UncheckedCast<HeapObject>(parameter3)}, &label6);
    ca_.Goto(&block15);
    if (label6.is_used()) {
      ca_.Bind(&label6);
      ca_.Goto(&block16);
    }
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    ca_.Goto(&block8, tmp3);
  }

  TNode<JSTypedArray> tmp7;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    compiler::CodeAssemblerLabel label8(&ca_);
    tmp7 = Cast_JSTypedArray_0(state_, TNode<HeapObject>{ca_.UncheckedCast<HeapObject>(parameter3)}, &label8);
    ca_.Goto(&block19);
    if (label8.is_used()) {
      ca_.Bind(&label8);
      ca_.Goto(&block20);
    }
  }

  TNode<JSTypedArray> tmp9;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp9 = ConstructByArrayBuffer_0(state_, TNode<Context>{parameter0}, TNode<Map>{tmp0}, TNode<JSArrayBuffer>{tmp5}, TNode<Object>{parameter4}, TNode<Object>{parameter5}, TorqueStructTypedArrayElementsInfo{TNode<UintPtrT>{tmp1}, TNode<Int32T>{tmp2}});
    CodeStubAssembler(state_).Return(tmp9);
  }

  TNode<JSReceiver> tmp10;
  if (block20.is_used()) {
    ca_.Bind(&block20);
    compiler::CodeAssemblerLabel label11(&ca_);
    tmp10 = Cast_JSReceiver_0(state_, TNode<HeapObject>{ca_.UncheckedCast<HeapObject>(parameter3)}, &label11);
    ca_.Goto(&block24);
    if (label11.is_used()) {
      ca_.Bind(&label11);
      ca_.Goto(&block25);
    }
  }

    compiler::TypedCodeAssemblerVariable<JSTypedArray> tmp13(&ca_);
    compiler::TypedCodeAssemblerVariable<UintPtrT> tmp14(&ca_);
    compiler::TypedCodeAssemblerVariable<JSReceiver> tmp15(&ca_);
  if (block19.is_used()) {
    ca_.Bind(&block19);
    compiler::CodeAssemblerLabel label12(&ca_);
    ConstructByTypedArray_0(state_, TNode<Context>{parameter0}, TNode<JSTypedArray>{tmp7}, &label12, &tmp13, &tmp14, &tmp15);
    if (label12.is_used()) {
      ca_.Bind(&label12);
      ca_.Goto(&block21);
    }
  }

  if (block21.is_used()) {
    ca_.Bind(&block21);
    ca_.Goto(&block6, tmp13.value(), tmp14.value(), tmp15.value());
  }

  if (block25.is_used()) {
    ca_.Bind(&block25);
    ca_.Goto(&block8, ca_.UncheckedCast<PrimitiveHeapObject>(parameter3));
  }

    compiler::TypedCodeAssemblerVariable<JSReceiver> tmp17(&ca_);
    compiler::TypedCodeAssemblerVariable<UintPtrT> tmp18(&ca_);
    compiler::TypedCodeAssemblerVariable<JSReceiver> tmp19(&ca_);
  if (block24.is_used()) {
    ca_.Bind(&block24);
    compiler::CodeAssemblerLabel label16(&ca_);
    ConstructByJSReceiver_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp10}, &label16, &tmp17, &tmp18, &tmp19);
    if (label16.is_used()) {
      ca_.Bind(&label16);
      ca_.Goto(&block26);
    }
  }

  if (block26.is_used()) {
    ca_.Bind(&block26);
    ca_.Goto(&block6, tmp17.value(), tmp18.value(), tmp19.value());
  }

  TNode<Object> phi_bb8_9;
  TNode<JSTypedArray> tmp20;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_9);
    tmp20 = ConstructByLength_0(state_, TNode<Context>{parameter0}, TNode<Map>{tmp0}, TNode<Object>{phi_bb8_9}, TorqueStructTypedArrayElementsInfo{TNode<UintPtrT>{tmp1}, TNode<Int32T>{tmp2}});
    CodeStubAssembler(state_).Return(tmp20);
  }

  TNode<JSReceiver> phi_bb6_9;
  TNode<UintPtrT> phi_bb6_10;
  TNode<JSReceiver> phi_bb6_11;
  TNode<JSTypedArray> tmp21;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_9, &phi_bb6_10, &phi_bb6_11);
    tmp21 = ConstructByArrayLike_0(state_, TNode<Context>{parameter0}, TNode<Map>{tmp0}, TNode<HeapObject>{phi_bb6_9}, TNode<UintPtrT>{phi_bb6_10}, TorqueStructTypedArrayElementsInfo{TNode<UintPtrT>{tmp1}, TNode<Int32T>{tmp2}}, TNode<JSReceiver>{phi_bb6_11});
    CodeStubAssembler(state_).Return(tmp21);
  }
}

TNode<JSTypedArray> TypedArraySpeciesCreate_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, const char* p_methodName, int31_t p_numArgs, TNode<JSTypedArray> p_exemplar, TNode<Object> p_arg0, TNode<Object> p_arg1, TNode<Object> p_arg2) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSTypedArray> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSTypedArray> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSFunction> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<Map> tmp2;
  TNode<BoolT> tmp3;
  TNode<BoolT> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = TypedArrayBuiltinsAssembler(state_).GetDefaultConstructor(TNode<Context>{p_context}, TNode<JSTypedArray>{p_exemplar});
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp2 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{p_exemplar, tmp1});
    tmp3 = CodeStubAssembler(state_).IsPrototypeTypedArrayPrototype(TNode<Context>{p_context}, TNode<Map>{tmp2});
    tmp4 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp3});
    ca_.Branch(tmp4, &block4, std::vector<Node*>{}, &block5, std::vector<Node*>{});
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    ca_.Goto(&block3);
  }

  TNode<BoolT> tmp5;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp5 = CodeStubAssembler(state_).IsTypedArraySpeciesProtectorCellInvalid();
    ca_.Branch(tmp5, &block6, std::vector<Node*>{}, &block7, std::vector<Node*>{});
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block3);
  }

  TNode<JSTypedArray> tmp6;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp6 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kCreateTypedArray, p_context, tmp0, tmp0, p_arg0, p_arg1, p_arg2));
    ca_.Goto(&block1, tmp6);
  }

  TNode<JSReceiver> tmp7;
  TNode<JSReceiver> tmp8;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp7 = CodeStubAssembler(state_).SpeciesConstructor(TNode<Context>{p_context}, TNode<Object>{p_exemplar}, TNode<JSReceiver>{tmp0});
    compiler::CodeAssemblerLabel label9(&ca_);
    tmp8 = Cast_Constructor_0(state_, TNode<HeapObject>{tmp7}, &label9);
    ca_.Goto(&block14);
    if (label9.is_used()) {
      ca_.Bind(&label9);
      ca_.Goto(&block15);
    }
  }

  if (block15.is_used()) {
    ca_.Bind(&block15);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Oddball> tmp10;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp10 = Undefined_0(state_);
    if (((CodeStubAssembler(state_).ConstexprInt31Equal(p_numArgs, 1)))) {
      ca_.Goto(&block16);
    } else {
      ca_.Goto(&block17);
    }
  }

  TNode<JSReceiver> tmp11;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp11 = CodeStubAssembler(state_).Construct(TNode<Context>{p_context}, TNode<JSReceiver>{tmp8}, TNode<Object>{p_arg0});
    ca_.Goto(&block18, tmp11);
  }

  TNode<JSReceiver> tmp12;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp12 = CodeStubAssembler(state_).Construct(TNode<Context>{p_context}, TNode<JSReceiver>{tmp8}, TNode<Object>{p_arg0}, TNode<Object>{p_arg1}, TNode<Object>{p_arg2});
    ca_.Goto(&block18, tmp12);
  }

  TNode<Object> phi_bb18_7;
  TNode<JSTypedArray> tmp13;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_7);
    tmp13 = TypedArrayBuiltinsAssembler(state_).ValidateTypedArray(TNode<Context>{p_context}, TNode<Object>{phi_bb18_7}, p_methodName);
    ca_.Goto(&block1, tmp13);
  }

  TNode<JSTypedArray> phi_bb1_5;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_5);
    ca_.Goto(&block23, phi_bb1_5);
  }

  TNode<JSTypedArray> phi_bb23_5;
    ca_.Bind(&block23, &phi_bb23_5);
  return TNode<JSTypedArray>{phi_bb23_5};
}

TNode<JSTypedArray> TypedArraySpeciesCreateByLength_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, const char* p_methodName, TNode<JSTypedArray> p_exemplar, TNode<UintPtrT> p_length) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Oddball> tmp1;
  TNode<Oddball> tmp2;
  TNode<JSTypedArray> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<UintPtrT> tmp5;
  TNode<BoolT> tmp6;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = Convert_Number_uintptr_0(state_, TNode<UintPtrT>{p_length});
    tmp1 = Undefined_0(state_);
    tmp2 = Undefined_0(state_);
    tmp3 = TypedArraySpeciesCreate_0(state_, TNode<Context>{p_context}, p_methodName, 1, TNode<JSTypedArray>{p_exemplar}, TNode<Object>{tmp0}, TNode<Object>{tmp1}, TNode<Object>{tmp2});
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp5 = CodeStubAssembler(state_).LoadReference<UintPtrT>(CodeStubAssembler::Reference{tmp3, tmp4});
    tmp6 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp5}, TNode<UintPtrT>{p_length});
    ca_.Branch(tmp6, &block2, std::vector<Node*>{}, &block3, std::vector<Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{p_context}, MessageTemplate::kTypedArrayTooShort);
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<JSTypedArray>{tmp3};
}

TNode<JSTypedArray> TypedArraySpeciesCreateByBuffer_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, const char* p_methodName, TNode<JSTypedArray> p_exemplar, TNode<JSArrayBuffer> p_buffer, TNode<UintPtrT> p_beginByteOffset, TNode<UintPtrT> p_newLength) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Number> tmp1;
  TNode<JSTypedArray> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = Convert_Number_uintptr_0(state_, TNode<UintPtrT>{p_beginByteOffset});
    tmp1 = Convert_Number_uintptr_0(state_, TNode<UintPtrT>{p_newLength});
    tmp2 = TypedArraySpeciesCreate_0(state_, TNode<Context>{p_context}, p_methodName, 3, TNode<JSTypedArray>{p_exemplar}, TNode<Object>{p_buffer}, TNode<Object>{tmp0}, TNode<Object>{tmp1});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<JSTypedArray>{tmp2};
}

TNode<JSArrayBuffer> Cast_JSArrayBuffer_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError) {
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

  TNode<JSArrayBuffer> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_JSArrayBuffer_0(state_, TNode<HeapObject>{tmp0}, &label3);
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
  return TNode<JSArrayBuffer>{tmp2};
}

}  // namespace internal
}  // namespace v8

