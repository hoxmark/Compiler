require_relative 'testlib'

prepare do
	executable "./oracle"
	testing "./calculator"


	to :scan, "-s"
	to :parse, ""
	to :eval, "-e"
end

doing :scan do
	pass "3+2", "number3 + number2"
	pass "2+4*3+3", "number2 + number4 * number3 + number3"
	pass "2+4%3+(2+5)", "number2 + number4 % number3 + ( number2 + number5 )"
	pass "111*22", "number111 * number22"
	pass "((((((4+2)*3)+4)/5)%6)+1)", "( ( ( ( ( ( number4 + number2 ) * number3 ) + number4 ) / number5 ) % number6 ) + number1 )"
	pass "3+2()", "number3 + number2 ( )"
	pass "3++", "number3 + +"
	fail "r+3", "Scan error: found invalid character r at line 1"
	fail "3+2a", "Scan error: found invalid character a at line 1"
	fail "4^2+2", "Scan error: found invalid character ^ at line 1"

end

doing :parse do
	pass "2+4*3+3", ""
	pass "2+4%3+(2+5)", ""
	pass "111*22", ""
	pass "((((((4+2)*3)+4)/5)%6)+1)", ""
	pass "3+2;5+4", ""
	fail "()", "Parse error: found invalid token ) at line 1"
	fail "(1+2", "Parse error: expected ) found EOF at line 1"
	fail "3++", "Parse error: found invalid token + at line 1"

end

doing :eval do
	pass "((2+43)%6+12)/3; (2**3**2+19)%8", "5\n3"
	pass "22*2-(9*5-5)", "4"
	pass "18*4-22%3", "71"
	pass "(14%10)**2; 14%10**2; 14%(10**2)", "16\n14\n14"
	pass "44**2*2%33%10", "1"
	pass "0-(180**2%454-(10**2*2-(2**2+2)*5))", "4"
	pass "81%3+10/3*3%3", "0"
	pass "5+2%3+22*7+(16+(2*4))", "185"
	fail "2**100", "Semantic error: number -9223372036854775808 out of bounds at line 1"
	fail "1/2;\n3/0", "Semantic error: dividing 3 with zero at line 2"
	fail "3+3;\n3/(3-3)", "Semantic error: dividing 3 with zero at line 2"
	fail "1/1;\n0/0", "Semantic error: dividing 0 with zero at line 2"

end



test!
