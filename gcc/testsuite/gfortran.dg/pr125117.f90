! { dg-do run }
! { dg-options "-O0" }
! PR fortran/125117

program test
  implicit none
  character(len=64) :: fixed
  character(:), allocatable :: got
  fixed = 'hello world'
  got = getName(fixed)
  if (trim(got) == 'hello world') then
    print *, 'PASS'
  else
    print *, 'FAIL: got=[', trim(got), ']'
    call abort()
  end if
contains
  function getName(fixed) result(name)
    character(len=64), intent(in) :: fixed
    character(:), allocatable :: name
    name = fixed
  end function
end program
