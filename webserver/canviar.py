
string = 'https%3A%2F%2Fgithub.com%2FOriolVentosa%2FPractiques%2Ftree%2Fmaster%2FIndividual'

a = string.split('%3A')

string = a[0] + ':' + a[1]

a = string.split('%2F')

b= ''
for x in range(0,len(a)):
    if x != 0:
        b = b + '/' + a[x]
    else:
        b = a[x]
string = b

print string

