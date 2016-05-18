	.text
.global main
main:
	pushl aaa
	pushl $likestr
	call printf
	addl $8, %esp
	ret
likestr: .string "I like you! aaa = %d\n"
aaa: .long 1234	
