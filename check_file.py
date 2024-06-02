import difflib
import shutil
import email_sender
import time

source = "/home/danbot/dev/bitflip_lab/transactions.txt"
dest = "/home/danbot/dev/bitflip_lab/running/old_transactions.txt"
def check_diff():
    old_t = open(dest, "r")
    transactions = open(source, "r")
    differ = difflib.Differ()
    diff = list(differ.compare(old_t.readlines(), transactions.readlines()))
    old_t.close()
    transactions.close()
    return diff

def cp_transactions():
    shutil.copyfile(source, dest)

def calc_diff(diff):
    diff_count = 0
    for l in diff:
        if not l[0] == " ":
            diff_count +=1
    return diff_count

def create_body(c, d):
    res = "There were " + str(c) + " changes in the transactions file:\n\n"
    for l in d:
        res += str(l)
    res += "\nFILE END\n"
    return res

while True:
    difference = check_diff()
    diff_count = calc_diff(difference)
    print(diff_count)
    if diff_count > 0:
        cp_transactions()
        email_sender.send_email("File changed by " + str(diff_count)+ " lines", create_body(diff_count, difference))
        print("copied and sent")
    time.sleep(60)