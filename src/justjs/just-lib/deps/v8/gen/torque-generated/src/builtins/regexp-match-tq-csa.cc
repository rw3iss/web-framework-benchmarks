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

TNode<Object> RegExpPrototypeMatchBody_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_regexp, TNode<String> p_string, bool p_isFastPath) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, String> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, String> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, String> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, String> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, String> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, String> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, String> block48(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, String> block50(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, String> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, String, String> block52(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, String> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, String> block57(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, String> block58(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, String, String> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, String> block44(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, String> block59(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, String> block60(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, String, HeapObject> block61(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, String, String, String, Object> block83(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, String, String, String, Object> block84(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, String, String, String, Object, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block102(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, String, String, String, Object, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block103(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, String, String> block105(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, String, String> block106(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, String, String> block107(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, String, String> block108(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, String, String, Object> block109(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, String, String> block114(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, String, String> block115(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, String, String> block116(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, String> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block121(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    if ((p_isFastPath)) {
      ca_.Goto(&block2);
    } else {
      ca_.Goto(&block3);
    }
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    ca_.Goto(&block4);
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block4);
  }

  TNode<BoolT> tmp0;
  TNode<BoolT> tmp1;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp0 = RegExpBuiltinsAssembler(state_).FlagGetter(TNode<Context>{p_context}, TNode<Object>{p_regexp}, JSRegExp::Flag::kGlobal, p_isFastPath);
    tmp1 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp0});
    ca_.Branch(tmp1, &block9, std::vector<Node*>{}, &block10, std::vector<Node*>{});
  }

  TNode<BoolT> tmp2;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp2 = FromConstexpr_bool_constexpr_bool_0(state_, p_isFastPath);
    ca_.Branch(tmp2, &block11, std::vector<Node*>{}, &block12, std::vector<Node*>{});
  }

  TNode<Object> tmp3;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp3 = RegExpPrototypeExecBodyFast_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{p_regexp}, TNode<String>{p_string});
    ca_.Goto(&block13, tmp3);
  }

  TNode<Object> tmp4;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp4 = RegExpExec_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{p_regexp}, TNode<String>{p_string});
    ca_.Goto(&block13, tmp4);
  }

  TNode<Object> phi_bb13_4;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_4);
    ca_.Goto(&block1, phi_bb13_4);
  }

  TNode<BoolT> tmp5;
  TNode<Number> tmp6;
  TNode<FixedArray> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<BoolT> tmp10;
  TNode<String> tmp11;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp5 = RegExpBuiltinsAssembler(state_).FlagGetter(TNode<Context>{p_context}, TNode<Object>{p_regexp}, JSRegExp::Flag::kUnicode, p_isFastPath);
    tmp6 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    StoreLastIndex_0(state_, TNode<Context>{p_context}, TNode<Object>{p_regexp}, TNode<Number>{tmp6}, p_isFastPath);
    std::tie(tmp7, tmp8, tmp9) = NewGrowableFixedArray_0(state_).Flatten();
    tmp10 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp11 = CodeStubAssembler(state_).EmptyStringConstant();
    if ((p_isFastPath)) {
      ca_.Goto(&block19);
    } else {
      ca_.Goto(&block20);
    }
  }

  TNode<JSRegExp> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<HeapObject> tmp14;
  TNode<FixedArray> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<Smi> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<UintPtrT> tmp22;
  TNode<UintPtrT> tmp23;
  TNode<BoolT> tmp24;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp12 = UnsafeCast_JSRegExp_0(state_, TNode<Context>{p_context}, TNode<Object>{p_regexp});
    tmp13 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp14 = CodeStubAssembler(state_).LoadReference<HeapObject>(CodeStubAssembler::Reference{tmp12, tmp13});
    tmp15 = UnsafeCast_FixedArray_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp14});
    tmp16 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp17 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp18 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp19 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp15, tmp18});
    tmp20 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp19});
    tmp21 = Convert_intptr_constexpr_int31_0(state_, JSRegExp::kTagIndex);
    tmp22 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp21});
    tmp23 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp20});
    tmp24 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp22}, TNode<UintPtrT>{tmp23});
    ca_.Branch(tmp24, &block28, std::vector<Node*>{}, &block29, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<HeapObject> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<Object> tmp30;
  TNode<Smi> tmp31;
  TNode<Smi> tmp32;
  TNode<BoolT> tmp33;
  if (block28.is_used()) {
    ca_.Bind(&block28);
    tmp25 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp26 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp21}, TNode<IntPtrT>{tmp25});
    tmp27 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp16}, TNode<IntPtrT>{tmp26});
    std::tie(tmp28, tmp29) = NewReference_Object_0(state_, TNode<HeapObject>{tmp15}, TNode<IntPtrT>{tmp27}).Flatten();
    tmp30 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp28, tmp29});
    tmp31 = UnsafeCast_Smi_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp30});
    tmp32 = FromConstexpr_Smi_constexpr_int31_0(state_, JSRegExp::ATOM);
    tmp33 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp31}, TNode<Smi>{tmp32});
    ca_.Branch(tmp33, &block22, std::vector<Node*>{}, &block23, std::vector<Node*>{tmp10, tmp11});
  }

  if (block29.is_used()) {
    ca_.Bind(&block29);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp34;
  TNode<IntPtrT> tmp35;
  TNode<IntPtrT> tmp36;
  TNode<Smi> tmp37;
  TNode<IntPtrT> tmp38;
  TNode<IntPtrT> tmp39;
  TNode<UintPtrT> tmp40;
  TNode<UintPtrT> tmp41;
  TNode<BoolT> tmp42;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    tmp34 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp35 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp36 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp37 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp15, tmp36});
    tmp38 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp37});
    tmp39 = Convert_intptr_constexpr_int31_0(state_, JSRegExp::kAtomPatternIndex);
    tmp40 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp39});
    tmp41 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp38});
    tmp42 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp40}, TNode<UintPtrT>{tmp41});
    ca_.Branch(tmp42, &block35, std::vector<Node*>{}, &block36, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp43;
  TNode<IntPtrT> tmp44;
  TNode<IntPtrT> tmp45;
  TNode<HeapObject> tmp46;
  TNode<IntPtrT> tmp47;
  TNode<Object> tmp48;
  TNode<String> tmp49;
  TNode<BoolT> tmp50;
  if (block35.is_used()) {
    ca_.Bind(&block35);
    tmp43 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp44 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp39}, TNode<IntPtrT>{tmp43});
    tmp45 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp34}, TNode<IntPtrT>{tmp44});
    std::tie(tmp46, tmp47) = NewReference_Object_0(state_, TNode<HeapObject>{tmp15}, TNode<IntPtrT>{tmp45}).Flatten();
    tmp48 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp46, tmp47});
    tmp49 = UnsafeCast_String_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp48});
    tmp50 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block23, tmp50, tmp49);
  }

  if (block36.is_used()) {
    ca_.Bind(&block36);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> phi_bb23_8;
  TNode<String> phi_bb23_9;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_8, &phi_bb23_9);
    ca_.Goto(&block21, phi_bb23_8, phi_bb23_9);
  }

  if (block20.is_used()) {
    ca_.Bind(&block20);
    ca_.Goto(&block21, tmp10, tmp11);
  }

  TNode<BoolT> phi_bb21_8;
  TNode<String> phi_bb21_9;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_8, &phi_bb21_9);
    ca_.Goto(&block40, tmp7, tmp8, tmp9, phi_bb21_8, phi_bb21_9);
  }

  TNode<FixedArray> phi_bb40_5;
  TNode<IntPtrT> phi_bb40_6;
  TNode<IntPtrT> phi_bb40_7;
  TNode<BoolT> phi_bb40_8;
  TNode<String> phi_bb40_9;
  TNode<BoolT> tmp51;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_5, &phi_bb40_6, &phi_bb40_7, &phi_bb40_8, &phi_bb40_9);
    tmp51 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Branch(tmp51, &block38, std::vector<Node*>{phi_bb40_5, phi_bb40_6, phi_bb40_7, phi_bb40_8, phi_bb40_9}, &block39, std::vector<Node*>{phi_bb40_5, phi_bb40_6, phi_bb40_7, phi_bb40_8, phi_bb40_9});
  }

  TNode<FixedArray> phi_bb38_5;
  TNode<IntPtrT> phi_bb38_6;
  TNode<IntPtrT> phi_bb38_7;
  TNode<BoolT> phi_bb38_8;
  TNode<String> phi_bb38_9;
  TNode<String> tmp52;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_5, &phi_bb38_6, &phi_bb38_7, &phi_bb38_8, &phi_bb38_9);
    tmp52 = CodeStubAssembler(state_).EmptyStringConstant();
    if ((p_isFastPath)) {
      ca_.Goto(&block45, phi_bb38_5, phi_bb38_6, phi_bb38_7, phi_bb38_8, phi_bb38_9);
    } else {
      ca_.Goto(&block46, phi_bb38_5, phi_bb38_6, phi_bb38_7, phi_bb38_8, phi_bb38_9);
    }
  }

  TNode<FixedArray> phi_bb45_5;
  TNode<IntPtrT> phi_bb45_6;
  TNode<IntPtrT> phi_bb45_7;
  TNode<BoolT> phi_bb45_8;
  TNode<String> phi_bb45_9;
  TNode<JSRegExp> tmp53;
  TNode<RegExpMatchInfo> tmp54;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_5, &phi_bb45_6, &phi_bb45_7, &phi_bb45_8, &phi_bb45_9);
    tmp53 = UnsafeCast_JSRegExp_0(state_, TNode<Context>{p_context}, TNode<Object>{p_regexp});
    compiler::CodeAssemblerLabel label55(&ca_);
    tmp54 = RegExpPrototypeExecBodyWithoutResultFast_0(state_, TNode<Context>{p_context}, TNode<JSRegExp>{tmp53}, TNode<String>{p_string}, &label55);
    ca_.Goto(&block48, phi_bb45_5, phi_bb45_6, phi_bb45_7, phi_bb45_8, phi_bb45_9);
    if (label55.is_used()) {
      ca_.Bind(&label55);
      ca_.Goto(&block49, phi_bb45_5, phi_bb45_6, phi_bb45_7, phi_bb45_8, phi_bb45_9);
    }
  }

  TNode<FixedArray> phi_bb49_5;
  TNode<IntPtrT> phi_bb49_6;
  TNode<IntPtrT> phi_bb49_7;
  TNode<BoolT> phi_bb49_8;
  TNode<String> phi_bb49_9;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_5, &phi_bb49_6, &phi_bb49_7, &phi_bb49_8, &phi_bb49_9);
    ca_.Goto(&block44, phi_bb49_5, phi_bb49_6, phi_bb49_7, phi_bb49_8, phi_bb49_9);
  }

  TNode<FixedArray> phi_bb48_5;
  TNode<IntPtrT> phi_bb48_6;
  TNode<IntPtrT> phi_bb48_7;
  TNode<BoolT> phi_bb48_8;
  TNode<String> phi_bb48_9;
  if (block48.is_used()) {
    ca_.Bind(&block48, &phi_bb48_5, &phi_bb48_6, &phi_bb48_7, &phi_bb48_8, &phi_bb48_9);
    ca_.Branch(phi_bb48_8, &block50, std::vector<Node*>{phi_bb48_5, phi_bb48_6, phi_bb48_7, phi_bb48_8, phi_bb48_9}, &block51, std::vector<Node*>{phi_bb48_5, phi_bb48_6, phi_bb48_7, phi_bb48_8, phi_bb48_9});
  }

  TNode<FixedArray> phi_bb50_5;
  TNode<IntPtrT> phi_bb50_6;
  TNode<IntPtrT> phi_bb50_7;
  TNode<BoolT> phi_bb50_8;
  TNode<String> phi_bb50_9;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_5, &phi_bb50_6, &phi_bb50_7, &phi_bb50_8, &phi_bb50_9);
    ca_.Goto(&block52, phi_bb50_5, phi_bb50_6, phi_bb50_7, phi_bb50_8, phi_bb50_9, phi_bb50_9);
  }

  TNode<FixedArray> phi_bb51_5;
  TNode<IntPtrT> phi_bb51_6;
  TNode<IntPtrT> phi_bb51_7;
  TNode<BoolT> phi_bb51_8;
  TNode<String> phi_bb51_9;
  TNode<Object> tmp56;
  TNode<Object> tmp57;
  TNode<Smi> tmp58;
  TNode<Smi> tmp59;
  TNode<String> tmp60;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_5, &phi_bb51_6, &phi_bb51_7, &phi_bb51_8, &phi_bb51_9);
    tmp56 = CodeStubAssembler(state_).UnsafeLoadFixedArrayElement(TNode<RegExpMatchInfo>{tmp54}, RegExpMatchInfo::kFirstCaptureIndex);
    tmp57 = CodeStubAssembler(state_).UnsafeLoadFixedArrayElement(TNode<RegExpMatchInfo>{tmp54}, (CodeStubAssembler(state_).ConstexprInt31Add(RegExpMatchInfo::kFirstCaptureIndex, 1)));
    tmp58 = UnsafeCast_Smi_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp56});
    tmp59 = UnsafeCast_Smi_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp57});
    tmp60 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kSubString, p_context, p_string, tmp58, tmp59));
    ca_.Goto(&block52, phi_bb51_5, phi_bb51_6, phi_bb51_7, phi_bb51_8, phi_bb51_9, tmp60);
  }

  TNode<FixedArray> phi_bb52_5;
  TNode<IntPtrT> phi_bb52_6;
  TNode<IntPtrT> phi_bb52_7;
  TNode<BoolT> phi_bb52_8;
  TNode<String> phi_bb52_9;
  TNode<String> phi_bb52_10;
  if (block52.is_used()) {
    ca_.Bind(&block52, &phi_bb52_5, &phi_bb52_6, &phi_bb52_7, &phi_bb52_8, &phi_bb52_9, &phi_bb52_10);
    ca_.Goto(&block47, phi_bb52_5, phi_bb52_6, phi_bb52_7, phi_bb52_8, phi_bb52_9, phi_bb52_10);
  }

  TNode<FixedArray> phi_bb46_5;
  TNode<IntPtrT> phi_bb46_6;
  TNode<IntPtrT> phi_bb46_7;
  TNode<BoolT> phi_bb46_8;
  TNode<String> phi_bb46_9;
  TNode<Object> tmp61;
  TNode<Oddball> tmp62;
  TNode<BoolT> tmp63;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_5, &phi_bb46_6, &phi_bb46_7, &phi_bb46_8, &phi_bb46_9);
    tmp61 = RegExpExec_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{p_regexp}, TNode<String>{p_string});
    tmp62 = Null_0(state_);
    tmp63 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp61}, TNode<HeapObject>{tmp62});
    ca_.Branch(tmp63, &block57, std::vector<Node*>{phi_bb46_5, phi_bb46_6, phi_bb46_7, phi_bb46_8, phi_bb46_9}, &block58, std::vector<Node*>{phi_bb46_5, phi_bb46_6, phi_bb46_7, phi_bb46_8, phi_bb46_9});
  }

  TNode<FixedArray> phi_bb57_5;
  TNode<IntPtrT> phi_bb57_6;
  TNode<IntPtrT> phi_bb57_7;
  TNode<BoolT> phi_bb57_8;
  TNode<String> phi_bb57_9;
  if (block57.is_used()) {
    ca_.Bind(&block57, &phi_bb57_5, &phi_bb57_6, &phi_bb57_7, &phi_bb57_8, &phi_bb57_9);
    ca_.Goto(&block44, phi_bb57_5, phi_bb57_6, phi_bb57_7, phi_bb57_8, phi_bb57_9);
  }

  TNode<FixedArray> phi_bb58_5;
  TNode<IntPtrT> phi_bb58_6;
  TNode<IntPtrT> phi_bb58_7;
  TNode<BoolT> phi_bb58_8;
  TNode<String> phi_bb58_9;
  TNode<Smi> tmp64;
  TNode<Object> tmp65;
  TNode<String> tmp66;
  if (block58.is_used()) {
    ca_.Bind(&block58, &phi_bb58_5, &phi_bb58_6, &phi_bb58_7, &phi_bb58_8, &phi_bb58_9);
    tmp64 = CodeStubAssembler(state_).SmiConstant(0);
    tmp65 = CodeStubAssembler(state_).GetProperty(TNode<Context>{p_context}, TNode<Object>{tmp61}, TNode<Object>{tmp64});
    tmp66 = CodeStubAssembler(state_).ToString_Inline(TNode<Context>{p_context}, TNode<Object>{tmp65});
    ca_.Goto(&block47, phi_bb58_5, phi_bb58_6, phi_bb58_7, phi_bb58_8, phi_bb58_9, tmp66);
  }

  TNode<FixedArray> phi_bb47_5;
  TNode<IntPtrT> phi_bb47_6;
  TNode<IntPtrT> phi_bb47_7;
  TNode<BoolT> phi_bb47_8;
  TNode<String> phi_bb47_9;
  TNode<String> phi_bb47_10;
  TNode<BoolT> tmp67;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_5, &phi_bb47_6, &phi_bb47_7, &phi_bb47_8, &phi_bb47_9, &phi_bb47_10);
    tmp67 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb47_6}, TNode<IntPtrT>{phi_bb47_7});
    ca_.Branch(tmp67, &block83, std::vector<Node*>{phi_bb47_5, phi_bb47_6, phi_bb47_7, phi_bb47_8, phi_bb47_9, phi_bb47_10, phi_bb47_10, phi_bb47_10}, &block84, std::vector<Node*>{phi_bb47_5, phi_bb47_6, phi_bb47_7, phi_bb47_8, phi_bb47_9, phi_bb47_10, phi_bb47_10, phi_bb47_10});
  }

  TNode<FixedArray> phi_bb44_5;
  TNode<IntPtrT> phi_bb44_6;
  TNode<IntPtrT> phi_bb44_7;
  TNode<BoolT> phi_bb44_8;
  TNode<String> phi_bb44_9;
  TNode<IntPtrT> tmp68;
  TNode<BoolT> tmp69;
  if (block44.is_used()) {
    ca_.Bind(&block44, &phi_bb44_5, &phi_bb44_6, &phi_bb44_7, &phi_bb44_8, &phi_bb44_9);
    tmp68 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp69 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb44_7}, TNode<IntPtrT>{tmp68});
    ca_.Branch(tmp69, &block59, std::vector<Node*>{phi_bb44_5, phi_bb44_6, phi_bb44_7, phi_bb44_8, phi_bb44_9}, &block60, std::vector<Node*>{phi_bb44_5, phi_bb44_6, phi_bb44_7, phi_bb44_8, phi_bb44_9});
  }

  TNode<FixedArray> phi_bb59_5;
  TNode<IntPtrT> phi_bb59_6;
  TNode<IntPtrT> phi_bb59_7;
  TNode<BoolT> phi_bb59_8;
  TNode<String> phi_bb59_9;
  TNode<Oddball> tmp70;
  if (block59.is_used()) {
    ca_.Bind(&block59, &phi_bb59_5, &phi_bb59_6, &phi_bb59_7, &phi_bb59_8, &phi_bb59_9);
    tmp70 = Null_0(state_);
    ca_.Goto(&block61, phi_bb59_5, phi_bb59_6, phi_bb59_7, phi_bb59_8, phi_bb59_9, tmp70);
  }

  TNode<FixedArray> phi_bb60_5;
  TNode<IntPtrT> phi_bb60_6;
  TNode<IntPtrT> phi_bb60_7;
  TNode<BoolT> phi_bb60_8;
  TNode<String> phi_bb60_9;
  TNode<NativeContext> tmp71;
  TNode<Map> tmp72;
  TNode<IntPtrT> tmp73;
  TNode<FixedArray> tmp74;
  TNode<Smi> tmp75;
  TNode<JSArray> tmp76;
  if (block60.is_used()) {
    ca_.Bind(&block60, &phi_bb60_5, &phi_bb60_6, &phi_bb60_7, &phi_bb60_8, &phi_bb60_9);
    tmp71 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{p_context});
    tmp72 = CodeStubAssembler(state_).LoadJSArrayElementsMap(ElementsKind::PACKED_ELEMENTS, TNode<NativeContext>{tmp71});
    tmp73 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp74 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb60_5}, TNode<IntPtrT>{tmp73}, TNode<IntPtrT>{phi_bb60_7}, TNode<IntPtrT>{phi_bb60_7});
    tmp75 = Convert_Smi_intptr_0(state_, TNode<IntPtrT>{phi_bb60_7});
    tmp76 = CodeStubAssembler(state_).AllocateJSArray(TNode<Map>{tmp72}, TNode<FixedArrayBase>{tmp74}, TNode<Smi>{tmp75});
    ca_.Goto(&block61, phi_bb60_5, phi_bb60_6, phi_bb60_7, phi_bb60_8, phi_bb60_9, tmp76);
  }

  TNode<FixedArray> phi_bb61_5;
  TNode<IntPtrT> phi_bb61_6;
  TNode<IntPtrT> phi_bb61_7;
  TNode<BoolT> phi_bb61_8;
  TNode<String> phi_bb61_9;
  TNode<HeapObject> phi_bb61_11;
  if (block61.is_used()) {
    ca_.Bind(&block61, &phi_bb61_5, &phi_bb61_6, &phi_bb61_7, &phi_bb61_8, &phi_bb61_9, &phi_bb61_11);
    ca_.Goto(&block1, phi_bb61_11);
  }

  TNode<FixedArray> phi_bb83_5;
  TNode<IntPtrT> phi_bb83_6;
  TNode<IntPtrT> phi_bb83_7;
  TNode<BoolT> phi_bb83_8;
  TNode<String> phi_bb83_9;
  TNode<String> phi_bb83_10;
  TNode<String> phi_bb83_11;
  TNode<Object> phi_bb83_12;
  TNode<IntPtrT> tmp77;
  TNode<IntPtrT> tmp78;
  TNode<IntPtrT> tmp79;
  TNode<IntPtrT> tmp80;
  TNode<IntPtrT> tmp81;
  TNode<IntPtrT> tmp82;
  TNode<FixedArray> tmp83;
  if (block83.is_used()) {
    ca_.Bind(&block83, &phi_bb83_5, &phi_bb83_6, &phi_bb83_7, &phi_bb83_8, &phi_bb83_9, &phi_bb83_10, &phi_bb83_11, &phi_bb83_12);
    tmp77 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp78 = CodeStubAssembler(state_).WordSar(TNode<IntPtrT>{phi_bb83_6}, TNode<IntPtrT>{tmp77});
    tmp79 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb83_6}, TNode<IntPtrT>{tmp78});
    tmp80 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    tmp81 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp79}, TNode<IntPtrT>{tmp80});
    tmp82 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp83 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb83_5}, TNode<IntPtrT>{tmp82}, TNode<IntPtrT>{phi_bb83_7}, TNode<IntPtrT>{tmp81});
    ca_.Goto(&block84, tmp83, tmp81, phi_bb83_7, phi_bb83_8, phi_bb83_9, phi_bb83_10, phi_bb83_11, phi_bb83_12);
  }

  TNode<FixedArray> phi_bb84_5;
  TNode<IntPtrT> phi_bb84_6;
  TNode<IntPtrT> phi_bb84_7;
  TNode<BoolT> phi_bb84_8;
  TNode<String> phi_bb84_9;
  TNode<String> phi_bb84_10;
  TNode<String> phi_bb84_11;
  TNode<Object> phi_bb84_12;
  TNode<IntPtrT> tmp84;
  TNode<IntPtrT> tmp85;
  TNode<IntPtrT> tmp86;
  TNode<Smi> tmp87;
  TNode<IntPtrT> tmp88;
  TNode<IntPtrT> tmp89;
  TNode<IntPtrT> tmp90;
  TNode<UintPtrT> tmp91;
  TNode<UintPtrT> tmp92;
  TNode<BoolT> tmp93;
  if (block84.is_used()) {
    ca_.Bind(&block84, &phi_bb84_5, &phi_bb84_6, &phi_bb84_7, &phi_bb84_8, &phi_bb84_9, &phi_bb84_10, &phi_bb84_11, &phi_bb84_12);
    tmp84 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp85 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp86 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp87 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{phi_bb84_5, tmp86});
    tmp88 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp87});
    tmp89 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp90 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb84_7}, TNode<IntPtrT>{tmp89});
    tmp91 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb84_7});
    tmp92 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp88});
    tmp93 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp91}, TNode<UintPtrT>{tmp92});
    ca_.Branch(tmp93, &block102, std::vector<Node*>{phi_bb84_8, phi_bb84_9, phi_bb84_10, phi_bb84_11, phi_bb84_12, phi_bb84_7, phi_bb84_7, phi_bb84_7, phi_bb84_7}, &block103, std::vector<Node*>{phi_bb84_8, phi_bb84_9, phi_bb84_10, phi_bb84_11, phi_bb84_12, phi_bb84_7, phi_bb84_7, phi_bb84_7, phi_bb84_7});
  }

  TNode<BoolT> phi_bb102_8;
  TNode<String> phi_bb102_9;
  TNode<String> phi_bb102_10;
  TNode<String> phi_bb102_11;
  TNode<Object> phi_bb102_12;
  TNode<IntPtrT> phi_bb102_17;
  TNode<IntPtrT> phi_bb102_18;
  TNode<IntPtrT> phi_bb102_22;
  TNode<IntPtrT> phi_bb102_23;
  TNode<IntPtrT> tmp94;
  TNode<IntPtrT> tmp95;
  TNode<IntPtrT> tmp96;
  TNode<HeapObject> tmp97;
  TNode<IntPtrT> tmp98;
  TNode<Smi> tmp99;
  TNode<Smi> tmp100;
  TNode<BoolT> tmp101;
  if (block102.is_used()) {
    ca_.Bind(&block102, &phi_bb102_8, &phi_bb102_9, &phi_bb102_10, &phi_bb102_11, &phi_bb102_12, &phi_bb102_17, &phi_bb102_18, &phi_bb102_22, &phi_bb102_23);
    tmp94 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp95 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{phi_bb102_23}, TNode<IntPtrT>{tmp94});
    tmp96 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp84}, TNode<IntPtrT>{tmp95});
    std::tie(tmp97, tmp98) = NewReference_Object_0(state_, TNode<HeapObject>{phi_bb84_5}, TNode<IntPtrT>{tmp96}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp97, tmp98}, phi_bb102_12);
    tmp99 = CodeStubAssembler(state_).LoadStringLengthAsSmi(TNode<String>{phi_bb102_10});
    tmp100 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp101 = CodeStubAssembler(state_).SmiNotEqual(TNode<Smi>{tmp99}, TNode<Smi>{tmp100});
    ca_.Branch(tmp101, &block105, std::vector<Node*>{phi_bb102_8, phi_bb102_9, phi_bb102_10}, &block106, std::vector<Node*>{phi_bb102_8, phi_bb102_9, phi_bb102_10});
  }

  TNode<BoolT> phi_bb103_8;
  TNode<String> phi_bb103_9;
  TNode<String> phi_bb103_10;
  TNode<String> phi_bb103_11;
  TNode<Object> phi_bb103_12;
  TNode<IntPtrT> phi_bb103_17;
  TNode<IntPtrT> phi_bb103_18;
  TNode<IntPtrT> phi_bb103_22;
  TNode<IntPtrT> phi_bb103_23;
  if (block103.is_used()) {
    ca_.Bind(&block103, &phi_bb103_8, &phi_bb103_9, &phi_bb103_10, &phi_bb103_11, &phi_bb103_12, &phi_bb103_17, &phi_bb103_18, &phi_bb103_22, &phi_bb103_23);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> phi_bb105_8;
  TNode<String> phi_bb105_9;
  TNode<String> phi_bb105_10;
  if (block105.is_used()) {
    ca_.Bind(&block105, &phi_bb105_8, &phi_bb105_9, &phi_bb105_10);
    ca_.Goto(&block40, phi_bb84_5, phi_bb84_6, tmp90, phi_bb105_8, phi_bb105_9);
  }

  TNode<BoolT> phi_bb106_8;
  TNode<String> phi_bb106_9;
  TNode<String> phi_bb106_10;
  TNode<Object> tmp102;
  if (block106.is_used()) {
    ca_.Bind(&block106, &phi_bb106_8, &phi_bb106_9, &phi_bb106_10);
    tmp102 = LoadLastIndex_0(state_, TNode<Context>{p_context}, TNode<Object>{p_regexp}, p_isFastPath);
    if ((p_isFastPath)) {
      ca_.Goto(&block107, phi_bb106_8, phi_bb106_9, phi_bb106_10);
    } else {
      ca_.Goto(&block108, phi_bb106_8, phi_bb106_9, phi_bb106_10);
    }
  }

  TNode<BoolT> phi_bb107_8;
  TNode<String> phi_bb107_9;
  TNode<String> phi_bb107_10;
  if (block107.is_used()) {
    ca_.Bind(&block107, &phi_bb107_8, &phi_bb107_9, &phi_bb107_10);
    ca_.Goto(&block109, phi_bb107_8, phi_bb107_9, phi_bb107_10, tmp102);
  }

  TNode<BoolT> phi_bb108_8;
  TNode<String> phi_bb108_9;
  TNode<String> phi_bb108_10;
  TNode<Number> tmp103;
  if (block108.is_used()) {
    ca_.Bind(&block108, &phi_bb108_8, &phi_bb108_9, &phi_bb108_10);
    tmp103 = CodeStubAssembler(state_).ToLength_Inline(TNode<Context>{p_context}, TNode<Object>{tmp102});
    ca_.Goto(&block109, phi_bb108_8, phi_bb108_9, phi_bb108_10, tmp103);
  }

  TNode<BoolT> phi_bb109_8;
  TNode<String> phi_bb109_9;
  TNode<String> phi_bb109_10;
  TNode<Object> phi_bb109_12;
  TNode<Number> tmp104;
  TNode<Number> tmp105;
  if (block109.is_used()) {
    ca_.Bind(&block109, &phi_bb109_8, &phi_bb109_9, &phi_bb109_10, &phi_bb109_12);
    tmp104 = UnsafeCast_Number_0(state_, TNode<Context>{p_context}, TNode<Object>{phi_bb109_12});
    tmp105 = RegExpBuiltinsAssembler(state_).AdvanceStringIndex(TNode<String>{p_string}, TNode<Number>{tmp104}, TNode<BoolT>{tmp5}, p_isFastPath);
    if ((p_isFastPath)) {
      ca_.Goto(&block114, phi_bb109_8, phi_bb109_9, phi_bb109_10);
    } else {
      ca_.Goto(&block115, phi_bb109_8, phi_bb109_9, phi_bb109_10);
    }
  }

  TNode<BoolT> phi_bb114_8;
  TNode<String> phi_bb114_9;
  TNode<String> phi_bb114_10;
  TNode<BoolT> tmp106;
  if (block114.is_used()) {
    ca_.Bind(&block114, &phi_bb114_8, &phi_bb114_9, &phi_bb114_10);
    tmp106 = FromConstexpr_bool_constexpr_bool_0(state_, (CodeStubAssembler(state_).ConstexprUintPtrLessThan(String::kMaxLength, kSmiMaxValue)));
    CodeStubAssembler(state_).StaticAssert(TNode<BoolT>{tmp106}, "static_assert(kMaxStringLengthFitsSmi) at src/builtins/regexp-match.tq:113:9");
    ca_.Goto(&block116, phi_bb114_8, phi_bb114_9, phi_bb114_10);
  }

  TNode<BoolT> phi_bb115_8;
  TNode<String> phi_bb115_9;
  TNode<String> phi_bb115_10;
  if (block115.is_used()) {
    ca_.Bind(&block115, &phi_bb115_8, &phi_bb115_9, &phi_bb115_10);
    ca_.Goto(&block116, phi_bb115_8, phi_bb115_9, phi_bb115_10);
  }

  TNode<BoolT> phi_bb116_8;
  TNode<String> phi_bb116_9;
  TNode<String> phi_bb116_10;
  if (block116.is_used()) {
    ca_.Bind(&block116, &phi_bb116_8, &phi_bb116_9, &phi_bb116_10);
    StoreLastIndex_0(state_, TNode<Context>{p_context}, TNode<Object>{p_regexp}, TNode<Number>{tmp105}, p_isFastPath);
    ca_.Goto(&block40, phi_bb84_5, phi_bb84_6, tmp90, phi_bb116_8, phi_bb116_9);
  }

  TNode<FixedArray> phi_bb39_5;
  TNode<IntPtrT> phi_bb39_6;
  TNode<IntPtrT> phi_bb39_7;
  TNode<BoolT> phi_bb39_8;
  TNode<String> phi_bb39_9;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_5, &phi_bb39_6, &phi_bb39_7, &phi_bb39_8, &phi_bb39_9);
    VerifiedUnreachable_0(state_);
  }

  TNode<Object> phi_bb1_3;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_3);
    ca_.Goto(&block121, phi_bb1_3);
  }

  TNode<Object> phi_bb121_3;
    ca_.Bind(&block121, &phi_bb121_3);
  return TNode<Object>{phi_bb121_3};
}

TNode<Object> FastRegExpPrototypeMatchBody_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSRegExp> p_receiver, TNode<String> p_string) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Object> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = RegExpPrototypeMatchBody_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{p_receiver}, TNode<String>{p_string}, true);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Object>{tmp0};
}

TNode<Object> SlowRegExpPrototypeMatchBody_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_receiver, TNode<String> p_string) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Object> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = RegExpPrototypeMatchBody_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{p_receiver}, TNode<String>{p_string}, false);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Object>{tmp0};
}

TF_BUILTIN(RegExpMatchFast, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSRegExp> parameter1 = UncheckedCast<JSRegExp>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<String> parameter2 = UncheckedCast<String>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Object> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FastRegExpPrototypeMatchBody_0(state_, TNode<Context>{parameter0}, TNode<JSRegExp>{parameter1}, TNode<String>{parameter2});
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TF_BUILTIN(RegExpPrototypeMatch, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kReceiver));
USE(parameter1);
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::kString));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  TNode<String> tmp1;
  TNode<JSRegExp> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    CodeStubAssembler(state_).ThrowIfNotJSReceiver(TNode<Context>{parameter0}, TNode<Object>{parameter1}, MessageTemplate::kIncompatibleMethodReceiver, "RegExp.prototype.@@match");
    tmp0 = UnsafeCast_JSReceiver_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = CodeStubAssembler(state_).ToString_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter2});
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_FastJSRegExp_0(state_, TNode<Context>{parameter0}, TNode<HeapObject>{tmp0}, &label3);
    ca_.Goto(&block3);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block4);
    }
  }

  TNode<Object> tmp4;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp4 = SlowRegExpPrototypeMatchBody_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0}, TNode<String>{tmp1});
    CodeStubAssembler(state_).Return(tmp4);
  }

  TNode<Object> tmp5;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp5 = CodeStubAssembler(state_).CallBuiltin(Builtins::kRegExpMatchFast, parameter0, tmp2, tmp1);
    CodeStubAssembler(state_).Return(tmp5);
  }
}

TNode<BoolT> Is_FastJSRegExp_JSReceiver_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSRegExp> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_FastJSRegExp_0(state_, TNode<Context>{p_context}, TNode<HeapObject>{p_o}, &label1);
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

}  // namespace internal
}  // namespace v8

