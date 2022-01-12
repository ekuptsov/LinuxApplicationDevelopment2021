cc = meson.get_compiler('c')

doxygen = find_program('doxygen', required: false)
if doxygen.found()
  message('Doxygen found')
  run_target('docs', command : [doxygen, meson.source_root() + '/docs/Doxyfile'])
else
  warning('Documentation disabled without doxygen')
endif

# custom_target('manpage',
#      depends : exe,
#      input: exe.path(),
#      output: exe.name() + '.man',
#      command: [h2m, '-N', '@INPUT@', '-o', '@OUTPUT@'],
#      build_by_default: true)