project('regexp substitution string', 'c')
executable('esub', 'esub.c')

test_1 = find_program('./test_1.sh')
test_2 = find_program('./test_2.sh')
test('sed wo pockets', test_1)
test('sed with 2 reversed pockets', test_2)
