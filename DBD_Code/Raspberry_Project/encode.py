import binascii


user_inp = input("Enter the string you wish to encode to send a message: ")

gsm = ("@£$¥èéùìòÇ\nØø\rÅåΔ_ΦΓΛΩΠΨΣΘΞ\x1bÆæßÉ !\"#¤%&'()*+,-./0123456789:;<=>?"
       "¡ABCDEFGHIJKLMNOPQRSTUVWXYZÄÖÑÜ§¿abcdefghijklmnopqrstuvwxyzäöñüà")
ext = ("````````````````````^```````````````````{}`````\\````````````[~]`"
       "|````````````````````````````````````€``````````````````````````")

def gsm_encode(plain):
    result = ""
    for item in plain:
        index = gsm.find(item);
        if index != -1:
            result += chr(index)
            continue
        index = ext.find(item)
        if index != -1:
            result += chr(27) + chr(index)
    return binascii.b2a_hex(result.encode('utf-8'))

print(gsm_encode(user_inp))
