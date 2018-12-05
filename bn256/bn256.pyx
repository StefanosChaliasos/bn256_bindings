cimport bn256
from cpython.version cimport PY_MAJOR_VERSION


cdef unicode _ustring(s):
    if type(s) is unicode:
        # fast path for most common case(s)
        return <unicode>s
    elif PY_MAJOR_VERSION < 3 and isinstance(s, bytes):
        # only accept byte strings in Python 2.x, not in Py3
        return (<bytes>s).decode('ascii')
    elif isinstance(s, unicode):
        # an evil cast to <unicode> might work here in some(!) cases,
        # depending on what the further processing does.  to be safe,
        # we can always create a copy instead
        return unicode(s)
    else:
        raise TypeError(...)

def int_to_element(integer):
    integer = str(integer)
    integer = integer.encode('utf-8')
    temp = bn256.int_to_element_serialized(integer)
    elem = [t.decode("utf-8") for t in temp]
    return elem

def element_to_int(elem, max_number):
    temp = [c.encode('utf-8') for c in elem]
    integer = bn256.element_to_int_serialized(temp, max_number)
    return int(integer.decode("utf-8"))

def validate_element(elem):
    temp = [c.encode('utf-8') for c in elem]
    return bn256.is_valid_element_serialized(temp)

def get_random_element():
    temp = bn256.get_random_element_serialized()
    elem = [t.decode("utf-8") for t in temp]
    return elem

def get_modulus():
    temp = bn256.get_modulus_serialized()
    modulus = temp.decode("utf-8")
    return int(modulus)

def get_order():
    temp = bn256.get_order_serialized()
    order = temp.decode("utf-8")
    return int(order)

def get_generator():
    temp = bn256.get_generator_serialized()
    generator = [t.decode("utf-8") for t in temp]
    return generator

def keygen():
    secret, public = bn256.keygen_serialized()
    return secret.decode("utf-8"), [t.decode("utf-8") for t in public]

def mul(elem, integer):
    temp = [c.encode('utf-8') for c in elem]
    integer = str(integer)
    temp2 = integer.encode('utf-8')
    res = bn256.mul_serialized(temp, temp2)
    return [c.decode("utf-8") for c in res]

def add(elem1, elem2):
    temp1 = [c.encode('utf-8') for c in elem1]
    temp2 = [c.encode('utf-8') for c in elem2]
    res = bn256.add_serialized(temp1, temp2)
    return [c.decode("utf-8") for c in res]

def is_equal(elem1, elem2):
    temp1 = [c.encode('utf-8') for c in elem1]
    temp2 = [c.encode('utf-8') for c in elem2]
    res = bn256.is_equal_serialized(temp1, temp2)
    return res

def inverse(elem):
    temp = [c.encode('utf-8') for c in elem]
    res = bn256.inverse_serialized(temp)
    return [c.decode("utf-8") for c in res]

def sign(pub, secret, message):
    temp1 = [c.encode('utf-8') for c in pub]
    temp2 = str(secret).encode('utf-8')
    temp3 = message.encode('utf-8')
    signature = bn256.bls_sign(temp1, temp2, temp3)
    return [c.decode("utf-8") for c in signature]

def verify(sign, pub, message):
    temp1 = [c.encode('utf-8') for c in sign]
    temp2 = [c.encode('utf-8') for c in pub]
    temp3 = message.encode('utf-8')
    return bn256.bls_verify(temp1, temp2, temp3)
