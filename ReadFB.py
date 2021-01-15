import firebase_admin
from firebase_admin import credentials
from firebase_admin import db

def dbconnect(get_url, get_cred):
    
    cred = credentials.Certificate(get_cred)

    default_app = firebase_admin.initialize_app(cred, {'databaseURL':get_url})
    
    ref = db.reference()

    row = str(ref.get())

    return row

def dbpush(get_url, get_cred, get_ref, get_child ,get_push, get_value):
    
    cred = credentials.Certificate(get_cred)
    
    default_app = firebase_admin.initialize_app(cred, {'databaseURL':get_url})

    if get_push == "":
        ref = db.reference().child(get_ref)
        if get_value != "":
            ref.child(get_child).set(get_value)
        else:
            ref.push(get_child)

    elif get_child == "":
        ref = db.reference().child(get_ref)
        if get_value != "":
            ref.child(get_push).set(get_value)
        else:
            ref.push(get_push)

    else:
        ref = db.reference().child(get_ref).child(get_child)
        if get_value != "":
            ref.child(get_push).set(get_value)
        else:
            ref.push(get_push)

    ref = db.reference()

    row = str(ref.get())

    return row

def dbdel(get_url, get_cred, get_ref, get_child, get_del):

    cred = credentials.Certificate(get_cred)

    default_app = firebase_admin.initialize_app(cred, {'databaseURL':get_url})

    ref = db.reference()

    bef_row = ref.get()

    if get_del != "":
        ref.child(get_ref).child(get_child).child(get_del).delete()

    elif get_child != "":
        ref.child(get_ref).child(get_child).delete()

    else:
        ref.child(get_ref).delete()

    aft_row = ref.get()

    if bef_row != aft_row:
        return str(ref.get())

    return None