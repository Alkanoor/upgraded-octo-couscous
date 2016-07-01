
remplacement = [[ "'d"," would"],["'re", " are"],["da","the"],["em","them"],["u","you"],["\\xc2"," "],["\\xa0"," "],
                ["\\t"," "],["\\n"," "],["yo","you"],["ur","you"],["won't", "will not"],["can't", "cannot"],
                ["i'm", "i am"],["im", "i am"],["ain't", "is not"],["'ll", "will"],["'t", " not"],["'ve", " have"],
                ["'s", " is"],["isnt"," is not"]]

def replace(comment,remplacement):
    
    words = comment.split(' ')
    words = [word.lower() for word in words]
    for index,word in enumerate(words) :
        for i in range(len(remplacement)):
            if word==remplacement[i][0]:
                #print word
                words[index] = remplacement[i][1]
    
    comment2 = ""
    for word in words :
        comment2+=word+" "
    return comment2

def replace_stop_word(comment,remplacement,swpath='stopwords.txt'):
    
    if swpath is not None:
        with open(swpath) as f:
            stop_words = f.readlines()
        
    words = comment.split(' ')
    words = [word.lower() for word in words]
    for index,word in enumerate(words) :
        
        isStopWord = False
        if swpath is not None:

            #check if in stop word
            for j in range(len(stop_words)):
                if word == stop_words[j][:-1]:
                    words[index]=''
                    isStopWord = True
                
        if not isStopWord:
            for i in range(len(remplacement)):
                if word==remplacement[i][0]:
                    #print word
                    words[index] = remplacement[i][1]
    
    comment2 = ""
    for word in words :
        comment2+=word+" "
    return comment2

def endsWith(word,end):
    if len(word)<len(end):
        return False
    return word[-len(end):]==end

def contains(word,content):
    if len(word)<len(content):
        return False
    for i in range(len(word)-len(content)+1):
        if word[i:i+len(content)]==content:
            return True
    return False

def startsWith(word,start):
    if len(word)<len(start):
        return False
    return word[:len(start)]==start

def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        return False
    
def stem(comment):
    
    words = comment.split(' ')
    words = [word.lower() for word in words]
    
    for index,word in enumerate(words):
        if endsWith(word,'ies'):
            words[index] = word[:-3]+'y'
        elif endsWith(word,'s'):
            words[index] = word[:-1]
        elif endsWith(word,'ing'):
            words[index] = word[:-3]
        elif endsWith(word,'tard'):
            words[index] = word[:-4]
        
        elif startsWith(word,'@') and word!='@':
            words[index] = '@expression'
        
        elif contains(word,'*') and word!='*':
            words[index] = '*expression'
        
        else:
            try:
                float(word)
                words[index] = '09expression'
            except ValueError:
                pass
    
    comment_stemmed = ''
    for word in words:
        comment_stemmed+=word+' '
    return comment_stemmed

def supressFinalSpace(line):
    if line[-1]==' ':
        line = line[:-1]
        return supressFinalSpace(line)
    else :
        return line



# # Best Score : 0.816039873131
# ### only apply replaceInsideword twice +  replace "-" to space. No stemming, No stop word

# In[68]:

listReplaceInside = [['-',' ']]

def replaceInsideword(word,listReplace  = listReplaceInside):
    change = False
    for subset in listReplace:
        if contains(word,subset[0]):
            for i in range(len(word)-len(subset[0])+1):
                if word[i:i+len(subset[0])]==subset[0]:
                    word = word[0:i]+subset[1]+word[i+len(subset[0]):]   
                    change = True
    
    if change:
        return replaceInsideword(word,listReplaceInside)
    
    return word  


# In[11]:

with open('train.csv','r') as f:
    lines = f.readlines()

with open('train_temporaire','w') as f:
    for line in lines:
        lineReplace = replaceInsideword(line,listReplaceInside)
        lineReplace = replace_stop_word(lineReplace,remplacement,swpath=None)
        #add a space between de """ and the first letter 
        lineReplace = lineReplace[0:5]+' '+lineReplace[5:]
        lineReplace = lineReplace[:-4]+' '+lineReplace[-4:]
        lineReplace = supressFinalSpace(lineReplace)

        f.write(lineReplace)
        
with open('test.csv','r') as f:
    lines = f.readlines()

with open('test_temporaire','w') as f:
    for line in lines:
        lineReplace = replaceInsideword(line,listReplaceInside)
        lineReplace = replace_stop_word(lineReplace,remplacement,swpath=None)
        #add a space between de """ and the first letter 
        lineReplace = lineReplace[0:3]+' '+lineReplace[3:]
        #important adding space before the """ in the end otherwise some '\n' will be skiped by stemming
        lineReplace = lineReplace[:-4]+' '+lineReplace[-4:]
        lineReplace = supressFinalSpace(lineReplace)
        f.write(lineReplace)
        

with open('train_temporaire','r') as f:
    lines = f.readlines()

with open('train_doublerepl_replTiret.csv','w') as f:
    for line in lines:
        lineReplace = replace_stop_word(line,remplacement,swpath=None)
        #add a space between de """ and the first letter 
        lineReplace = lineReplace[0:5]+' '+lineReplace[5:]
        lineReplace = lineReplace[:-4]+' '+lineReplace[-4:]
        lineReplace = supressFinalSpace(lineReplace)

        f.write(lineReplace)
        
with open('test_conv_SW4a.csv','r') as f:
    lines = f.readlines()

with open('test_doublerepl_replTiret.csv','w') as f:
    for line in lines:
        lineReplace = replace_stop_word(line,remplacement,swpath=None)
        #add a space between de """ and the first letter 
        lineReplace = lineReplace[0:3]+' '+lineReplace[3:]
        #important adding space before the """ in the end otherwise some '\n' will be skiped by stemming
        lineReplace = lineReplace[:-4]+' '+lineReplace[-4:]
        lineReplace = supressFinalSpace(lineReplace)
        f.write(lineReplace)
        