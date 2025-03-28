// SPDX-FileCopyrightText: Copyright 2023 yuzu Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "core/hle/kernel/k_page_table.h"
#include "core/hle/kernel/k_scoped_lock.h"
#include "core/hle/kernel/svc_types.h"

namespace Kernel {

class KProcessPageTable {
private:
    KPageTable m_page_table;

public:
    KProcessPageTable(KernelCore& kernel) : m_page_table(kernel) {}

    Result Initialize(Svc::CreateProcessFlag as_type, bool enable_aslr, bool enable_das_merge,
                      bool from_back, KMemoryManager::Pool pool, KProcessAddress code_address,
                      size_t code_size, KSystemResource* system_resource,
                      KResourceLimit* resource_limit, Core::Memory::Memory& memory,
                      KProcessAddress aslr_space_start) {
        R_RETURN(m_page_table.InitializeForProcess(
            as_type, enable_aslr, enable_das_merge, from_back, pool, code_address, code_size,
            system_resource, resource_limit, memory, aslr_space_start));
    }

    void Finalize() {
        m_page_table.Finalize();
    }

    Core::Memory::Memory& GetMemory() {
        return m_page_table.GetMemory();
    }

    Core::Memory::Memory& GetMemory() const {
        return m_page_table.GetMemory();
    }

    Common::PageTable& GetImpl() {
        return m_page_table.GetImpl();
    }

    Common::PageTable& GetImpl() const {
        return m_page_table.GetImpl();
    }

    size_t GetNumGuardPages() const {
        return m_page_table.GetNumGuardPages();
    }

    KScopedLightLock AcquireDeviceMapLock() {
        return m_page_table.AcquireDeviceMapLock();
    }

    Result SetMemoryPermission(KProcessAddress addr, size_t size, Svc::MemoryPermission perm) {
        R_RETURN(m_page_table.SetMemoryPermission(addr, size, perm));
    }

    Result SetProcessMemoryPermission(KProcessAddress addr, size_t size,
                                      Svc::MemoryPermission perm) {
        R_RETURN(m_page_table.SetProcessMemoryPermission(addr, size, perm));
    }

    Result SetMemoryAttribute(KProcessAddress addr, size_t size, KMemoryAttribute mask,
                              KMemoryAttribute attr) {
        R_RETURN(m_page_table.SetMemoryAttribute(addr, size, mask, attr));
    }

    Result SetHeapSize(KProcessAddress* out, size_t size) {
        R_RETURN(m_page_table.SetHeapSize(out, size));
    }

    Result SetMaxHeapSize(size_t size) {
        R_RETURN(m_page_table.SetMaxHeapSize(size));
    }

    Result QueryInfo(KMemoryInfo* out_info, Svc::PageInfo* out_page_info,
                     KProcessAddress addr) const {
        R_RETURN(m_page_table.QueryInfo(out_info, out_page_info, addr));
    }

    Result QueryPhysicalAddress(Svc::lp64::PhysicalMemoryInfo* out, KProcessAddress address) {
        R_RETURN(m_page_table.QueryPhysicalAddress(out, address));
    }

    Result QueryStaticMapping(KProcessAddress* out, KPhysicalAddress address, size_t size) {
        R_RETURN(m_page_table.QueryStaticMapping(out, address, size));
    }

    Result QueryIoMapping(KProcessAddress* out, KPhysicalAddress address, size_t size) {
        R_RETURN(m_page_table.QueryIoMapping(out, address, size));
    }

    Result MapMemory(KProcessAddress dst_address, KProcessAddress src_address, size_t size) {
        R_RETURN(m_page_table.MapMemory(dst_address, src_address, size));
    }

    Result UnmapMemory(KProcessAddress dst_address, KProcessAddress src_address, size_t size) {
        R_RETURN(m_page_table.UnmapMemory(dst_address, src_address, size));
    }

    Result MapCodeMemory(KProcessAddress dst_address, KProcessAddress src_address, size_t size) {
        R_RETURN(m_page_table.MapCodeMemory(dst_address, src_address, size));
    }

    Result UnmapCodeMemory(KProcessAddress dst_address, KProcessAddress src_address, size_t size) {
        R_RETURN(m_page_table.UnmapCodeMemory(dst_address, src_address, size));
    }

    Result MapIo(KPhysicalAddress phys_addr, size_t size, KMemoryPermission perm) {
        R_RETURN(m_page_table.MapIo(phys_addr, size, perm));
    }

    Result MapIoRegion(KProcessAddress dst_address, KPhysicalAddress phys_addr, size_t size,
                       Svc::MemoryMapping mapping, Svc::MemoryPermission perm) {
        R_RETURN(m_page_table.MapIoRegion(dst_address, phys_addr, size, mapping, perm));
    }

    Result UnmapIoRegion(KProcessAddress dst_address, KPhysicalAddress phys_addr, size_t size,
                         Svc::MemoryMapping mapping) {
        R_RETURN(m_page_table.UnmapIoRegion(dst_address, phys_addr, size, mapping));
    }

    Result MapStatic(KPhysicalAddress phys_addr, size_t size, KMemoryPermission perm) {
        R_RETURN(m_page_table.MapStatic(phys_addr, size, perm));
    }

    Result MapRegion(KMemoryRegionType region_type, KMemoryPermission perm) {
        R_RETURN(m_page_table.MapRegion(region_type, perm));
    }

    Result MapInsecureMemory(KProcessAddress address, size_t size) {
        R_RETURN(m_page_table.MapInsecureMemory(address, size));
    }

    Result UnmapInsecureMemory(KProcessAddress address, size_t size) {
        R_RETURN(m_page_table.UnmapInsecureMemory(address, size));
    }

    Result MapPageGroup(KProcessAddress addr, const KPageGroup& pg, KMemoryState state,
                        KMemoryPermission perm) {
        R_RETURN(m_page_table.MapPageGroup(addr, pg, state, perm));
    }

    Result UnmapPageGroup(KProcessAddress address, const KPageGroup& pg, KMemoryState state) {
        R_RETURN(m_page_table.UnmapPageGroup(address, pg, state));
    }

    Result MapPages(KProcessAddress* out_addr, size_t num_pages, size_t alignment,
                    KPhysicalAddress phys_addr, KMemoryState state, KMemoryPermission perm) {
        R_RETURN(m_page_table.MapPages(out_addr, num_pages, alignment, phys_addr, state, perm));
    }

    Result MapPages(KProcessAddress* out_addr, size_t num_pages, KMemoryState state,
                    KMemoryPermission perm) {
        R_RETURN(m_page_table.MapPages(out_addr, num_pages, state, perm));
    }

    Result MapPages(KProcessAddress address, size_t num_pages, KMemoryState state,
                    KMemoryPermission perm) {
        R_RETURN(m_page_table.MapPages(address, num_pages, state, perm));
    }

    Result UnmapPages(KProcessAddress addr, size_t num_pages, KMemoryState state) {
        R_RETURN(m_page_table.UnmapPages(addr, num_pages, state));
    }

    Result MakeAndOpenPageGroup(KPageGroup* out, KProcessAddress address, size_t num_pages,
                                KMemoryState state_mask, KMemoryState state,
                                KMemoryPermission perm_mask, KMemoryPermission perm,
                                KMemoryAttribute attr_mask, KMemoryAttribute attr) {
        R_RETURN(m_page_table.MakeAndOpenPageGroup(out, address, num_pages, state_mask, state,
                                                   perm_mask, perm, attr_mask, attr));
    }

    Result InvalidateProcessDataCache(KProcessAddress address, size_t size) {
        R_RETURN(m_page_table.InvalidateProcessDataCache(address, size));
    }

    Result ReadDebugMemory(KProcessAddress dst_address, KProcessAddress src_address, size_t size) {
        R_RETURN(m_page_table.ReadDebugMemory(dst_address, src_address, size));
    }

    Result ReadDebugIoMemory(KProcessAddress dst_address, KProcessAddress src_address, size_t size,
                             KMemoryState state) {
        R_RETURN(m_page_table.ReadDebugIoMemory(dst_address, src_address, size, state));
    }

    Result WriteDebugMemory(KProcessAddress dst_address, KProcessAddress src_address, size_t size) {
        R_RETURN(m_page_table.WriteDebugMemory(dst_address, src_address, size));
    }

    Result WriteDebugIoMemory(KProcessAddress dst_address, KProcessAddress src_address, size_t size,
                              KMemoryState state) {
        R_RETURN(m_page_table.WriteDebugIoMemory(dst_address, src_address, size, state));
    }

    Result LockForMapDeviceAddressSpace(bool* out_is_io, KProcessAddress address, size_t size,
                                        KMemoryPermission perm, bool is_aligned, bool check_heap) {
        R_RETURN(m_page_table.LockForMapDeviceAddressSpace(out_is_io, address, size, perm,
                                                           is_aligned, check_heap));
    }

    Result LockForUnmapDeviceAddressSpace(KProcessAddress address, size_t size, bool check_heap) {
        R_RETURN(m_page_table.LockForUnmapDeviceAddressSpace(address, size, check_heap));
    }

    Result UnlockForDeviceAddressSpace(KProcessAddress address, size_t size) {
        R_RETURN(m_page_table.UnlockForDeviceAddressSpace(address, size));
    }

    Result UnlockForDeviceAddressSpacePartialMap(KProcessAddress address, size_t size) {
        R_RETURN(m_page_table.UnlockForDeviceAddressSpacePartialMap(address, size));
    }

    Result OpenMemoryRangeForMapDeviceAddressSpace(KPageTableBase::MemoryRange* out,
                                                   KProcessAddress address, size_t size,
                                                   KMemoryPermission perm, bool is_aligned) {
        R_RETURN(m_page_table.OpenMemoryRangeForMapDeviceAddressSpace(out, address, size, perm,
                                                                      is_aligned));
    }

    Result OpenMemoryRangeForUnmapDeviceAddressSpace(KPageTableBase::MemoryRange* out,
                                                     KProcessAddress address, size_t size) {
        R_RETURN(m_page_table.OpenMemoryRangeForUnmapDeviceAddressSpace(out, address, size));
    }

    Result LockForIpcUserBuffer(KPhysicalAddress* out, KProcessAddress address, size_t size) {
        R_RETURN(m_page_table.LockForIpcUserBuffer(out, address, size));
    }

    Result UnlockForIpcUserBuffer(KProcessAddress address, size_t size) {
        R_RETURN(m_page_table.UnlockForIpcUserBuffer(address, size));
    }

    Result LockForTransferMemory(KPageGroup* out, KProcessAddress address, size_t size,
                                 KMemoryPermission perm) {
        R_RETURN(m_page_table.LockForTransferMemory(out, address, size, perm));
    }

    Result UnlockForTransferMemory(KProcessAddress address, size_t size, const KPageGroup& pg) {
        R_RETURN(m_page_table.UnlockForTransferMemory(address, size, pg));
    }

    Result LockForCodeMemory(KPageGroup* out, KProcessAddress address, size_t size) {
        R_RETURN(m_page_table.LockForCodeMemory(out, address, size));
    }

    Result UnlockForCodeMemory(KProcessAddress address, size_t size, const KPageGroup& pg) {
        R_RETURN(m_page_table.UnlockForCodeMemory(address, size, pg));
    }

    Result OpenMemoryRangeForProcessCacheOperation(KPageTableBase::MemoryRange* out,
                                                   KProcessAddress address, size_t size) {
        R_RETURN(m_page_table.OpenMemoryRangeForProcessCacheOperation(out, address, size));
    }

    Result CopyMemoryFromLinearToUser(KProcessAddress dst_addr, size_t size,
                                      KProcessAddress src_addr, KMemoryState src_state_mask,
                                      KMemoryState src_state, KMemoryPermission src_test_perm,
                                      KMemoryAttribute src_attr_mask, KMemoryAttribute src_attr) {
        R_RETURN(m_page_table.CopyMemoryFromLinearToUser(dst_addr, size, src_addr, src_state_mask,
                                                         src_state, src_test_perm, src_attr_mask,
                                                         src_attr));
    }

    Result CopyMemoryFromLinearToKernel(void* dst_addr, size_t size, KProcessAddress src_addr,
                                        KMemoryState src_state_mask, KMemoryState src_state,
                                        KMemoryPermission src_test_perm,
                                        KMemoryAttribute src_attr_mask, KMemoryAttribute src_attr) {
        R_RETURN(m_page_table.CopyMemoryFromLinearToKernel(dst_addr, size, src_addr, src_state_mask,
                                                           src_state, src_test_perm, src_attr_mask,
                                                           src_attr));
    }

    Result CopyMemoryFromUserToLinear(KProcessAddress dst_addr, size_t size,
                                      KMemoryState dst_state_mask, KMemoryState dst_state,
                                      KMemoryPermission dst_test_perm,
                                      KMemoryAttribute dst_attr_mask, KMemoryAttribute dst_attr,
                                      KProcessAddress src_addr) {
        R_RETURN(m_page_table.CopyMemoryFromUserToLinear(dst_addr, size, dst_state_mask, dst_state,
                                                         dst_test_perm, dst_attr_mask, dst_attr,
                                                         src_addr));
    }

    Result CopyMemoryFromKernelToLinear(KProcessAddress dst_addr, size_t size,
                                        KMemoryState dst_state_mask, KMemoryState dst_state,
                                        KMemoryPermission dst_test_perm,
                                        KMemoryAttribute dst_attr_mask, KMemoryAttribute dst_attr,
                                        void* src_addr) {
        R_RETURN(m_page_table.CopyMemoryFromKernelToLinear(dst_addr, size, dst_state_mask,
                                                           dst_state, dst_test_perm, dst_attr_mask,
                                                           dst_attr, src_addr));
    }

    Result CopyMemoryFromHeapToHeap(KProcessPageTable& dst_page_table, KProcessAddress dst_addr,
                                    size_t size, KMemoryState dst_state_mask,
                                    KMemoryState dst_state, KMemoryPermission dst_test_perm,
                                    KMemoryAttribute dst_attr_mask, KMemoryAttribute dst_attr,
                                    KProcessAddress src_addr, KMemoryState src_state_mask,
                                    KMemoryState src_state, KMemoryPermission src_test_perm,
                                    KMemoryAttribute src_attr_mask, KMemoryAttribute src_attr) {
        R_RETURN(m_page_table.CopyMemoryFromHeapToHeap(
            dst_page_table.m_page_table, dst_addr, size, dst_state_mask, dst_state, dst_test_perm,
            dst_attr_mask, dst_attr, src_addr, src_state_mask, src_state, src_test_perm,
            src_attr_mask, src_attr));
    }

    Result CopyMemoryFromHeapToHeapWithoutCheckDestination(
        KProcessPageTable& dst_page_table, KProcessAddress dst_addr, size_t size,
        KMemoryState dst_state_mask, KMemoryState dst_state, KMemoryPermission dst_test_perm,
        KMemoryAttribute dst_attr_mask, KMemoryAttribute dst_attr, KProcessAddress src_addr,
        KMemoryState src_state_mask, KMemoryState src_state, KMemoryPermission src_test_perm,
        KMemoryAttribute src_attr_mask, KMemoryAttribute src_attr) {
        R_RETURN(m_page_table.CopyMemoryFromHeapToHeapWithoutCheckDestination(
            dst_page_table.m_page_table, dst_addr, size, dst_state_mask, dst_state, dst_test_perm,
            dst_attr_mask, dst_attr, src_addr, src_state_mask, src_state, src_test_perm,
            src_attr_mask, src_attr));
    }

    Result SetupForIpc(KProcessAddress* out_dst_addr, size_t size, KProcessAddress src_addr,
                       KProcessPageTable& src_page_table, KMemoryPermission test_perm,
                       KMemoryState dst_state, bool send) {
        R_RETURN(m_page_table.SetupForIpc(out_dst_addr, size, src_addr, src_page_table.m_page_table,
                                          test_perm, dst_state, send));
    }

    Result CleanupForIpcServer(KProcessAddress address, size_t size, KMemoryState dst_state) {
        R_RETURN(m_page_table.CleanupForIpcServer(address, size, dst_state));
    }

    Result CleanupForIpcClient(KProcessAddress address, size_t size, KMemoryState dst_state) {
        R_RETURN(m_page_table.CleanupForIpcClient(address, size, dst_state));
    }

    Result MapPhysicalMemory(KProcessAddress address, size_t size) {
        R_RETURN(m_page_table.MapPhysicalMemory(address, size));
    }

    Result UnmapPhysicalMemory(KProcessAddress address, size_t size) {
        R_RETURN(m_page_table.UnmapPhysicalMemory(address, size));
    }

    Result MapPhysicalMemoryUnsafe(KProcessAddress address, size_t size) {
        R_RETURN(m_page_table.MapPhysicalMemoryUnsafe(address, size));
    }

    Result UnmapPhysicalMemoryUnsafe(KProcessAddress address, size_t size) {
        R_RETURN(m_page_table.UnmapPhysicalMemoryUnsafe(address, size));
    }

    Result UnmapProcessMemory(KProcessAddress dst_address, size_t size,
                              KProcessPageTable& src_page_table, KProcessAddress src_address) {
        R_RETURN(m_page_table.UnmapProcessMemory(dst_address, size, src_page_table.m_page_table,
                                                 src_address));
    }

    bool GetPhysicalAddress(KPhysicalAddress* out, KProcessAddress address) {
        return m_page_table.GetPhysicalAddress(out, address);
    }

    bool Contains(KProcessAddress addr, size_t size) const {
        return m_page_table.Contains(addr, size);
    }

    bool IsInAliasRegion(KProcessAddress addr, size_t size) const {
        return m_page_table.IsInAliasRegion(addr, size);
    }
    bool IsInHeapRegion(KProcessAddress addr, size_t size) const {
        return m_page_table.IsInHeapRegion(addr, size);
    }
    bool IsInUnsafeAliasRegion(KProcessAddress addr, size_t size) const {
        return m_page_table.IsInUnsafeAliasRegion(addr, size);
    }

    bool CanContain(KProcessAddress addr, size_t size, KMemoryState state) const {
        return m_page_table.CanContain(addr, size, state);
    }

    KProcessAddress GetAddressSpaceStart() const {
        return m_page_table.GetAddressSpaceStart();
    }
    KProcessAddress GetHeapRegionStart() const {
        return m_page_table.GetHeapRegionStart();
    }
    KProcessAddress GetAliasRegionStart() const {
        return m_page_table.GetAliasRegionStart();
    }
    KProcessAddress GetStackRegionStart() const {
        return m_page_table.GetStackRegionStart();
    }
    KProcessAddress GetKernelMapRegionStart() const {
        return m_page_table.GetKernelMapRegionStart();
    }
    KProcessAddress GetCodeRegionStart() const {
        return m_page_table.GetCodeRegionStart();
    }
    KProcessAddress GetAliasCodeRegionStart() const {
        return m_page_table.GetAliasCodeRegionStart();
    }

    size_t GetAddressSpaceSize() const {
        return m_page_table.GetAddressSpaceSize();
    }
    size_t GetHeapRegionSize() const {
        return m_page_table.GetHeapRegionSize();
    }
    size_t GetAliasRegionSize() const {
        return m_page_table.GetAliasRegionSize();
    }
    size_t GetStackRegionSize() const {
        return m_page_table.GetStackRegionSize();
    }
    size_t GetKernelMapRegionSize() const {
        return m_page_table.GetKernelMapRegionSize();
    }
    size_t GetCodeRegionSize() const {
        return m_page_table.GetCodeRegionSize();
    }
    size_t GetAliasCodeRegionSize() const {
        return m_page_table.GetAliasCodeRegionSize();
    }

    size_t GetNormalMemorySize() const {
        return m_page_table.GetNormalMemorySize();
    }

    size_t GetCodeSize() const {
        return m_page_table.GetCodeSize();
    }
    size_t GetCodeDataSize() const {
        return m_page_table.GetCodeDataSize();
    }

    size_t GetAliasCodeSize() const {
        return m_page_table.GetAliasCodeSize();
    }
    size_t GetAliasCodeDataSize() const {
        return m_page_table.GetAliasCodeDataSize();
    }

    u32 GetAllocateOption() const {
        return m_page_table.GetAllocateOption();
    }

    u32 GetAddressSpaceWidth() const {
        return m_page_table.GetAddressSpaceWidth();
    }

    KPhysicalAddress GetHeapPhysicalAddress(KVirtualAddress address) {
        return m_page_table.GetHeapPhysicalAddress(address);
    }

    u8* GetHeapVirtualPointer(KPhysicalAddress address) {
        return m_page_table.GetHeapVirtualPointer(address);
    }

    KVirtualAddress GetHeapVirtualAddress(KPhysicalAddress address) {
        return m_page_table.GetHeapVirtualAddress(address);
    }

    KBlockInfoManager* GetBlockInfoManager() {
        return m_page_table.GetBlockInfoManager();
    }

    KPageTable& GetBasePageTable() {
        return m_page_table;
    }

    const KPageTable& GetBasePageTable() const {
        return m_page_table;
    }

    size_t GetReservedRegionExtraSize() const {
        return m_page_table.GetReservedRegionExtraSize();
    }
};

} // namespace Kernel
