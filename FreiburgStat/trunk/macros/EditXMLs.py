import fileinput
#import argparse
from optparse import OptionParser


#_____________________________________________________________________________
#_____________________________________________________________________________

def cb(option, opt_str, value, parser):
#    print opt_str
#    print parser.rargs
    args=[]
    for arg in parser.rargs:
        if arg[0] != "-":
            args.append(arg)
        else:
            del parser.rargs[:len(args)]
            break
    if getattr(parser.values, option.dest):
        args.extend(getattr(parser.values, option.dest))
    setattr(parser.values, option.dest, args)



#_____________________________________________________________________________
#_____________________________________________________________________________
parser = OptionParser()
parser.add_option('-f', '--files',
                  action='callback',
                  callback=cb,
                  dest="files")

parser.add_option('--disableShapes',   action='callback', callback=cb, dest="disableShapes")
parser.add_option('-i',action="store_true",default=False)


(options, args) = parser.parse_args()


for f in options.files: 
    
    for  line in fileinput.FileInput(f, inplace= options.i):
        if "HistoSys" in line and not "<!--" in line:
            for shape in options.disableShapes:
                if shape in line:
                    line = "<!--" + line.replace("\n","") + "-->"

        print line
                

