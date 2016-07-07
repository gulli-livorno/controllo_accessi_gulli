#! python


import random
import make_html

INCounter= random.randint(1, 100)
OutCounter=random.randint(1, 100)
VisCoutner =INCounter-OutCounter
Status = "OK"

make_html.MakeHTML(INCounter,OutCounter,Status)
