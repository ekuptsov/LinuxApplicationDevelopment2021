project('binsearch', 'c', version: '0.0.1')

# meson = dependency('meson', version : '>=0.61.0')
prog = find_program('meson',
     version : '>=0.61.0',
     required : true,
)
subdir('po')

executable('binsearch', 'binsearch.c',)