#include "src/heap/factory.h"
#include "src/heap/factory-inl.h"
#include "src/heap/heap.h"
#include "src/heap/heap-inl.h"
#include "src/execution/isolate.h"

#include "torque-generated/internal-class-definitions-tq-inl.h"

#include "torque-generated/exported-class-definitions-tq-inl.h"

namespace v8 {
namespace internal {

Handle<SloppyArgumentsElements> Factory::NewSloppyArgumentsElements(int length, Handle<Context> context, Handle<FixedArray> arguments, AllocationType allocation_type) {
 int size = TorqueGeneratedSloppyArgumentsElements<SloppyArgumentsElements, FixedArrayBase>::SizeFor(length);
  ReadOnlyRoots roots(isolate());
  HeapObject result =
    isolate()->heap()->AllocateRawWith<Heap::kRetryOrFail>(size, allocation_type);
  result.set_map_after_allocation(roots.sloppy_arguments_elements_map(), SKIP_WRITE_BARRIER);
  Handle<SloppyArgumentsElements> result_handle(SloppyArgumentsElements::cast(result), isolate());
  result_handle->set_length(length);
  result_handle->set_context(*context, SKIP_WRITE_BARRIER);
  result_handle->set_arguments(*arguments, SKIP_WRITE_BARRIER);
  return result_handle;
}

Handle<OnHeapBasicBlockProfilerData> Factory::NewOnHeapBasicBlockProfilerData(Handle<ByteArray> block_ids, Handle<ByteArray> counts, Handle<String> name, Handle<String> schedule, Handle<String> code, int hash, AllocationType allocation_type) {
 int size = TorqueGeneratedOnHeapBasicBlockProfilerData<OnHeapBasicBlockProfilerData, HeapObject>::SizeFor();
  ReadOnlyRoots roots(isolate());
  HeapObject result =
    isolate()->heap()->AllocateRawWith<Heap::kRetryOrFail>(size, allocation_type);
  result.set_map_after_allocation(roots.on_heap_basic_block_profiler_data_map(), SKIP_WRITE_BARRIER);
  Handle<OnHeapBasicBlockProfilerData> result_handle(OnHeapBasicBlockProfilerData::cast(result), isolate());
  result_handle->set_block_ids(*block_ids, SKIP_WRITE_BARRIER);
  result_handle->set_counts(*counts, SKIP_WRITE_BARRIER);
  result_handle->set_name(*name, SKIP_WRITE_BARRIER);
  result_handle->set_schedule(*schedule, SKIP_WRITE_BARRIER);
  result_handle->set_code(*code, SKIP_WRITE_BARRIER);
  result_handle->set_hash(hash);
  return result_handle;
}

Handle<ExportedSubClassBase> Factory::NewExportedSubClassBase(Handle<HeapObject> a, Handle<HeapObject> b, AllocationType allocation_type) {
 int size = TorqueGeneratedExportedSubClassBase<ExportedSubClassBase, HeapObject>::SizeFor();
  ReadOnlyRoots roots(isolate());
  HeapObject result =
    isolate()->heap()->AllocateRawWith<Heap::kRetryOrFail>(size, allocation_type);
  result.set_map_after_allocation(roots.exported_sub_class_base_map(), SKIP_WRITE_BARRIER);
  Handle<ExportedSubClassBase> result_handle(ExportedSubClassBase::cast(result), isolate());
  result_handle->set_a(*a, SKIP_WRITE_BARRIER);
  result_handle->set_b(*b, SKIP_WRITE_BARRIER);
  return result_handle;
}

Handle<ExportedSubClass> Factory::NewExportedSubClass(Handle<HeapObject> a, Handle<HeapObject> b, int32_t c_field, int32_t d_field, int e_field, AllocationType allocation_type) {
 int size = TorqueGeneratedExportedSubClass<ExportedSubClass, ExportedSubClassBase>::SizeFor();
  ReadOnlyRoots roots(isolate());
  HeapObject result =
    isolate()->heap()->AllocateRawWith<Heap::kRetryOrFail>(size, allocation_type);
  result.set_map_after_allocation(roots.exported_sub_class_map(), SKIP_WRITE_BARRIER);
  Handle<ExportedSubClass> result_handle(ExportedSubClass::cast(result), isolate());
  result_handle->set_a(*a, SKIP_WRITE_BARRIER);
  result_handle->set_b(*b, SKIP_WRITE_BARRIER);
  result_handle->set_c_field(c_field);
  result_handle->set_d_field(d_field);
  result_handle->set_e_field(e_field);
  return result_handle;
}

Handle<ExportedSubClass2> Factory::NewExportedSubClass2(Handle<HeapObject> a, Handle<HeapObject> b, int32_t x_field, int32_t y_field, int z_field, AllocationType allocation_type) {
 int size = TorqueGeneratedExportedSubClass2<ExportedSubClass2, ExportedSubClassBase>::SizeFor();
  ReadOnlyRoots roots(isolate());
  HeapObject result =
    isolate()->heap()->AllocateRawWith<Heap::kRetryOrFail>(size, allocation_type);
  result.set_map_after_allocation(roots.exported_sub_class2_map(), SKIP_WRITE_BARRIER);
  Handle<ExportedSubClass2> result_handle(ExportedSubClass2::cast(result), isolate());
  result_handle->set_a(*a, SKIP_WRITE_BARRIER);
  result_handle->set_b(*b, SKIP_WRITE_BARRIER);
  result_handle->set_x_field(x_field);
  result_handle->set_y_field(y_field);
  result_handle->set_z_field(z_field);
  return result_handle;
}

}  // namespace internal
}  // namespace v8
