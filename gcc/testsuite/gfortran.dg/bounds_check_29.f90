! { dg-do run }
! { dg-additional-options "-fcheck=bounds" }
!
! Check that if an array descriptor reference uses variables, they are
! not used uninitialized by the bounds-checking code.


! PR fortran/125192
! Original example from Philippe Wautelet <philippe.wautelet at cnrs dot fr>

subroutine boundcheck_bug
  implicit none

  type isba_pe_t
    real, pointer, dimension(:,:) :: xwg
  end type isba_pe_t
  type isba_npe_t
    type(isba_pe_t), dimension(:), pointer :: al=>null()
  end type isba_npe_t
  type(isba_npe_t) :: npe

  allocate(npe%al(10))
  allocate(npe%al(1)%xwg(3,4))

  call random_number( npe%al(1)%xwg(:,3) )
end subroutine boundcheck_bug


! PR fortran/125198
! Original example from Neil Carlson <neil.n.carlson at gmail dot com>

module unstr_mesh_type
  type unstr_mesh
    real, allocatable :: normal(:,:)
  contains
    procedure :: compute_geometry
  end type
contains
  subroutine compute_geometry(this)
    class(unstr_mesh), intent(inout) :: this
    character(64) :: buf
    !print *, this%normal(1,1) ! THIS IS OKAY
    write(buf,*) this%normal(1,1)
    if (trim(buf) /= '   0.00000000') error stop 1
    !print *, this%normal(:,1) ! SPURIOUS BOUNDS ERROR HERE
    write(buf,*) this%normal(:,1)
    if (trim(buf) /= '   0.00000000       0.00000000       0.00000000') error stop 2
    !if (any(this%normal(:,1) /= 0.0)) error stop 2
  end subroutine
end module

subroutine test_pr125198
use unstr_mesh_type
type(unstr_mesh) :: mesh
allocate(mesh%normal(3,10), source=0.0)
call mesh%compute_geometry
end subroutine


call boundcheck_bug
call test_pr125198
end
