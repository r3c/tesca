#!/bin/sh

assert() {
	local expression="$4"
	local generate="$3"
	local input="$1"
	local output="$2"
	local reference="$(mktemp)"
	local result="$(mktemp)"

	cat > "$reference"

	eval "$generate" |
	"$(dirname "$0")/../tesca" -i "$input" -o "$output" "$expression" |
	sed 's/\r$//' > "$result"

	diff "$reference" "$result"

	local error="$?"

	rm "$reference" "$result"

	test "$error" -eq 0 || exit 1
}

assert_csv() {
	assert csv csv "$1" "$2"
}

assert_json() {
	assert json csv "$1" "$2"
}

# Basic CSV reading
assert_csv 'echo A,1' '_0, _1' << EOF
A,1
EOF

# Basic JSON reading
assert_json "echo '{\"1\": \"Hello\", \"key\": \"test\", \"complex\": [27, \"World!\", 3]}'" 'row.1, row.key, row.complex.0, row.complex.1, row.complex.2' << EOF
Hello,test,27,World!,3
EOF

# Count lines per tuple on 4000 lines file
assert_csv 'seq 1000 | while read i; do echo A,1; echo A,2; echo B,3; echo B,4; done' '_0, _1, sum(1)' << EOF
A,1,1000
A,2,1000
B,3,1000
B,4,1000
EOF

# Sum values on 1M lines file
assert_csv 'seq 1000000 | while read i; do echo A,$i; done' '_0, sum(_1)' << EOF
A,500000500000
EOF
