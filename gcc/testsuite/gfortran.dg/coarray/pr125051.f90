!{ dg-do link }

! Contributed by Paul Thomas  <pault@gcc.gnu.org>
! Check PR fortran/125051 is fixed.

module m
  integer, parameter :: ncells = 8, nsize = ncells+2
  integer, parameter :: head =2, tail = ncells + 1
  real :: second_derivative(ncells+2, ncells+2)
  type :: density_t
    real :: density(nsize)
    real:: derivative(nsize)
  end type
  type (density_t) :: n[*]
  real :: n_tail[*] = 0.0
  real :: n_head[*] = 0.0
contains
  subroutine sub
    integer :: image_no
    image_no = this_image()
    sync all
    if (image_no > 1) n_head = n[image_no -1]%density(tail)
    if (image_no < num_images()) n_tail = n[image_no +1]%density(head)
    sync all
  end
end module

program main
  use m
  implicit none
  call sub
contains
end program

