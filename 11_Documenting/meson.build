project('roman_binsearch', 'c', version: '0.0.1')

cc = meson.get_compiler('c')
m = find_program('meson',
     version : '>=0.61.0',
     required : true,
)

cc.has_header('argp.h')
cc.has_header('libintl.h')

h2m = find_program('help2man',
     required : true,
)

# dox = find_program('doxygen', required: true)

subdir('po')
subdir('docs')

exe = executable(
     'roman_binsearch',
     'roman_binsearch.c',
)

custom_target('manpage',
     depends : exe,
     input: exe,
     output: exe.name() + '.man',
     command: [h2m, '-N', './@INPUT@', '-o', '@OUTPUT@'],
     build_by_default: true)