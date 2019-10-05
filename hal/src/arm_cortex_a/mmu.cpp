#include <ARMCA9.h>

#include "mem_mmu.hpp"

#include "mmu.hpp"

using namespace mmu;

namespace {

    std::uint32_t section_normal;
    std::uint32_t section_normal_nc;
    std::uint32_t section_normal_cod;
    std::uint32_t section_normal_ro;
    std::uint32_t section_normal_rw;
    std::uint32_t section_so;
    std::uint32_t section_device_ro;
    std::uint32_t section_device_rw;
    std::uint32_t page4k_normal_cod_l1;
    std::uint32_t page4k_normal_cod_l2;
    std::uint32_t page4k_normal_ro_l1;
    std::uint32_t page4k_normal_ro_l2;
    std::uint32_t page4k_normal_rw_l1;
    std::uint32_t page4k_normal_rw_l2;
    std::uint32_t page4k_device_rw_l1;
    std::uint32_t page4k_device_rw_l2;
    std::uint32_t page64k_normal_cod_l1;
    std::uint32_t page64k_normal_cod_l2;
    std::uint32_t page64k_normal_ro_l1;
    std::uint32_t page64k_normal_ro_l2;
    std::uint32_t page64k_normal_rw_l1;
    std::uint32_t page64k_normal_rw_l2;
    std::uint32_t page64k_device_rw_l1;
    std::uint32_t page64k_device_rw_l2;

    void page4k_normal_cod(
        std::uint32_t&              descriptor_l1,
        std::uint32_t&              descriptor_l2,
        mmu_region_attributes_Type& region
    ) {
        region.rg_t         = mmu_region_size_Type::PAGE_4k;
        region.domain       = 0x0;
        region.e_t          = mmu_ecc_check_Type::ECC_DISABLED;
        region.g_t          = mmu_global_Type::GLOBAL;
        region.inner_norm_t = mmu_cacheability_Type::WB_WA;
        region.outer_norm_t = mmu_cacheability_Type::WB_WA;
        region.mem_t        = mmu_memory_Type::NORMAL;
        region.sec_t        = mmu_secure_Type::SECURE;
        region.xn_t         = mmu_execute_Type::EXECUTE;
        region.priv_t       = mmu_access_Type::READ;
        region.user_t       = mmu_access_Type::READ;
        region.sh_t         = mmu_shared_Type::NON_SHARED;
        MMU_GetPageDescriptor( &descriptor_l1, &descriptor_l2, region );
    }

    void page4k_normal_ro(
        std::uint32_t&              descriptor_l1,
        std::uint32_t&              descriptor_l2,
        mmu_region_attributes_Type& region
    ) {
        region.rg_t         = mmu_region_size_Type::PAGE_4k;
        region.domain       = 0x0;
        region.e_t          = mmu_ecc_check_Type::ECC_DISABLED;
        region.g_t          = mmu_global_Type::GLOBAL;
        region.inner_norm_t = mmu_cacheability_Type::WB_WA;
        region.outer_norm_t = mmu_cacheability_Type::WB_WA;
        region.mem_t        = mmu_memory_Type::NORMAL;
        region.sec_t        = mmu_secure_Type::SECURE;
        region.xn_t         = mmu_execute_Type::NON_EXECUTE;
        region.priv_t       = mmu_access_Type::READ;
        region.user_t       = mmu_access_Type::READ;
        region.sh_t         = mmu_shared_Type::NON_SHARED;
        MMU_GetPageDescriptor( &descriptor_l1, &descriptor_l2, region );
    }

    void page4k_normal_rw(
        std::uint32_t&              descriptor_l1,
        std::uint32_t&              descriptor_l2,
        mmu_region_attributes_Type& region
    ) {
        region.rg_t         = mmu_region_size_Type::PAGE_4k;
        region.domain       = 0x0;
        region.e_t          = mmu_ecc_check_Type::ECC_DISABLED;
        region.g_t          = mmu_global_Type::GLOBAL;
        region.inner_norm_t = mmu_cacheability_Type::WB_WA;
        region.outer_norm_t = mmu_cacheability_Type::WB_WA;
        region.mem_t        = mmu_memory_Type::NORMAL;
        region.sec_t        = mmu_secure_Type::SECURE;
        region.xn_t         = mmu_execute_Type::NON_EXECUTE;
        region.priv_t       = mmu_access_Type::RW;
        region.user_t       = mmu_access_Type::RW;
        region.sh_t         = mmu_shared_Type::NON_SHARED;
        MMU_GetPageDescriptor( &descriptor_l1, &descriptor_l2, region );
    }

    void page64k_normal_cod(
        std::uint32_t&              descriptor_l1,
        std::uint32_t&              descriptor_l2,
        mmu_region_attributes_Type& region
    ) {
        region.rg_t         = mmu_region_size_Type::PAGE_64k;
        region.domain       = 0x0;
        region.e_t          = mmu_ecc_check_Type::ECC_DISABLED;
        region.g_t          = mmu_global_Type::GLOBAL;
        region.inner_norm_t = mmu_cacheability_Type::WB_WA;
        region.outer_norm_t = mmu_cacheability_Type::WB_WA;
        region.mem_t        = mmu_memory_Type::NORMAL;
        region.sec_t        = mmu_secure_Type::SECURE;
        region.xn_t         = mmu_execute_Type::EXECUTE;
        region.priv_t       = mmu_access_Type::READ;
        region.user_t       = mmu_access_Type::READ;
        region.sh_t         = mmu_shared_Type::NON_SHARED;
        MMU_GetPageDescriptor( &descriptor_l1, &descriptor_l2, region );
    }

    void page64k_normal_ro(
        std::uint32_t&              descriptor_l1,
        std::uint32_t&              descriptor_l2,
        mmu_region_attributes_Type& region
    ) {
        region.rg_t         = mmu_region_size_Type::PAGE_64k;
        region.domain       = 0x0;
        region.e_t          = mmu_ecc_check_Type::ECC_DISABLED;
        region.g_t          = mmu_global_Type::GLOBAL;
        region.inner_norm_t = mmu_cacheability_Type::WB_WA;
        region.outer_norm_t = mmu_cacheability_Type::WB_WA;
        region.mem_t        = mmu_memory_Type::NORMAL;
        region.sec_t        = mmu_secure_Type::SECURE;
        region.xn_t         = mmu_execute_Type::NON_EXECUTE;
        region.priv_t       = mmu_access_Type::READ;
        region.user_t       = mmu_access_Type::READ;
        region.sh_t         = mmu_shared_Type::NON_SHARED;
        MMU_GetPageDescriptor( &descriptor_l1, &descriptor_l2, region );
    }

    void page64k_normal_rw(
        std::uint32_t&              descriptor_l1,
        std::uint32_t&              descriptor_l2,
        mmu_region_attributes_Type& region
    ) {
        region.rg_t         = mmu_region_size_Type::PAGE_64k;
        region.domain       = 0x0;
        region.e_t          = mmu_ecc_check_Type::ECC_DISABLED;
        region.g_t          = mmu_global_Type::GLOBAL;
        region.inner_norm_t = mmu_cacheability_Type::WB_WA;
        region.outer_norm_t = mmu_cacheability_Type::WB_WA;
        region.mem_t        = mmu_memory_Type::NORMAL;
        region.sec_t        = mmu_secure_Type::SECURE;
        region.xn_t         = mmu_execute_Type::NON_EXECUTE;
        region.priv_t       = mmu_access_Type::RW;
        region.user_t       = mmu_access_Type::RW;
        region.sh_t         = mmu_shared_Type::NON_SHARED;
        MMU_GetPageDescriptor( &descriptor_l1, &descriptor_l2, region );
    }

}

void mmu::generate_descriptors( void ) {
    mmu_region_attributes_Type region;

    section_normal( section_normal, region );
    section_normal_nc( section_normal_nc, region );
    section_normal_cod( section_normal_cod, region );
    section_normal_ro( section_normal_ro, region );
    section_normal_rw( section_normal_rw, region );
    section_so( section_so, region );
    section_device_ro( section_device_ro, region );
    section_device_rw( section_device_rw, region );
    page4k_normal_cod( page4k_normal_cod_l1, page4k_normal_cod_l2, region );
    page4k_normal_ro( page4k_normal_ro_l1, page4k_normal_ro_l2, region );
    page4k_normal_rw( page4k_normal_rw_l1, page4k_normal_rw_l2, region );
    page4k_device_rw( page4k_device_rw_l1, page4k_device_rw_l2, region );
    page64k_normal_cod( page64k_normal_cod_l1, page64k_normal_cod_l2, region );
    page64k_normal_ro( page64k_normal_ro_l1, page64k_normal_ro_l2, region );
    page64k_normal_rw( page64k_normal_rw_l1, page64k_normal_rw_l2, region );
    page64k_device_rw( page64k_device_rw_l1, page64k_device_rw_l2, region );
}

void mmu::map_section_fault( std::uintptr_t base, std::size_t length ) {
    MMU_TTSection(
        reinterpret_cast<std::uint32_t*>( l1_table_base ),
        base,
        length / l1_section_size,
        DESCRIPTOR_FAULT
    );
}

void mmu::map_4k_x( std::uintptr_t base, std::size_t length ) {
    MMU_TTPage4k(
        reinterpret_cast<std::uint32_t*>( l1_table_base ),
        base,
        length / l2_table_4k_section_size,
        page4k_normal_cod_l1,
        reinterpret_cast<std::uint32_t*>( l2_table_base ),
        page4k_normal_cod_l2
    );
}

void mmu::map_4k_ro( std::uintptr_t base, std::size_t length ) {
    MMU_TTPage4k(
        reinterpret_cast<std::uint32_t*>( l1_table_base ),
        base,
        length / l2_table_4k_section_size,
        page4k_normal_ro_l1,
        reinterpret_cast<std::uint32_t*>( l2_table_base ),
        page4k_normal_ro_l2
    );
}

void mmu::map_4k_rw( std::uintptr_t base, std::size_t length ) {
    MMU_TTPage4k(
        reinterpret_cast<std::uint32_t*>( l1_table_base ),
        base,
        length / l2_table_4k_section_size,
        page4k_normal_rw_l1,
        reinterpret_cast<std::uint32_t*>( l2_table_base ),
        page4k_normal_rw_l2
    );
}

void mmu::map_64k_x( std::uintptr_t base, std::size_t length ) {
    MMU_TTPage64k(
        reinterpret_cast<std::uint32_t*>( l1_table_base ),
        base,
        length / l2_table_64k_section_size,
        page64k_normal_cod_l1,
        reinterpret_cast<std::uint32_t*>( l2_table_base ),
        page64k_normal_cod_l2
    );
}

void mmu::map_64k_ro( std::uintptr_t base, std::size_t length ) {
    MMU_TTPage64k(
        reinterpret_cast<std::uint32_t*>( l1_table_base ),
        base,
        length / l2_table_64k_section_size,
        page64k_normal_ro_l1,
        reinterpret_cast<std::uint32_t*>( l2_table_base ),
        page64k_normal_ro_l2
    );
}

void mmu::map_64k_rw( std::uintptr_t base, std::size_t length ) {
    MMU_TTPage64k(
        reinterpret_cast<std::uint32_t*>( l1_table_base ),
        base,
        length / l2_table_64k_section_size,
        page64k_normal_rw_l1,
        reinterpret_cast<std::uint32_t*>( l2_table_base ),
        page64k_normal_rw_l2
    );
}
