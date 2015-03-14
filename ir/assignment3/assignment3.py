test = [824, 824 + 5, 824 + 5 + 214577]

def gap_encode(numbers):
    result = []

    previous = 0

    for number in numbers:
        result.append(number - previous)
        previous = number

    return result


def gap_decode(numbers):
    result = []

    total = 0

    for number in numbers:
        result.append(number + total)
        total = total + number

    return result


def vb_encode_number(n):
    n_bytes = []

    while True:
        n_bytes.insert(0, n % 128)

        if n < 128:
            break

        n = n / 128

    n_bytes[len(n_bytes) - 1] = n_bytes[len(n_bytes) - 1] + 128

    return n_bytes


def vb_encode(numbers):
    bytestream = []

    for n in numbers:
        n_bytes = vb_encode_number(n)

        bytestream.append(n_bytes)

    return bytestream


def vb_decode(bytestream):
    numbers = []

    n = 0

    for i in range(len(bytestream)):
        if bytestream[i] < 128:
            n = 128 * n + bytestream[i]
        else:
            n = 128 * n + (bytestream[i] - 128)
            numbers.append(n)
            n = 0

    return numbers

def unary_encode_number(number):
    return '1' * number + '0'


def unary_decode_number(byte):
    return byte.count('1')


def unary_encode(numbers):
    result = []

    for number in numbers:
        result.append(unary_encode_number(number))

    return result


def unary_decode(bytestream):
    result = []

    for i in range(len(bytestream.split('0')) - 1):
        result.append(unary_decode_number(bytestream[i]))

    return result


def gamma_encode(numbers):
    result = []

    for number in numbers:
        bin_number = bin(number)
        offset = bin_number.replace('0b' + bin_number[2], '')
        print(offset)
        length = unary_encode_number(len(offset))

        result.append([length, offset])

    return result


def gamma_decode(bytestream):
    result = []

    for length, offset in bytestream:
        result.append(int('0b1' + offset, 2))

    return result
