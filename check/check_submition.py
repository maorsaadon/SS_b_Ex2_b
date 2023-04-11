import glob, os , sys
import shutil
import subprocess
import re
import filecmp
passed = 1

def pars_input(f):
    submission_file = f
    git_rep = None
    ids = None
    commit = None
    print(submission_file)
    f= open(submission_file,"r")
    for line in f.readlines():
        if re.search(r'http', line):
            git_rep = line
            continue
        if re.search(r'\d{9}', line) and not re.search(r'\D.?\D.?\D', line):
            ids = line
            print(line)
            continue
        if re.search(r'.+', line):
            commit = line
            continue
    return git_rep , ids , commit
def run_cmd(cmd , verbos = 1, timeout = 20):
    if verbos == 1:
        print("running: " ,cmd)
    try:
        proc = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE , stderr=subprocess.PIPE )
        
        try:
            output = proc.communicate(timeout=timeout)[0].decode('utf8')
            if verbos == 1:
                print(output)
        except subprocess.TimeoutExpired:
            proc.kill()
            proc.wait()
            print("command timeout")
            return -2
            
        
        proc.wait()
        if (proc.returncode > 0 and proc.returncode < 20) or proc.returncode > 100:
           raise Exception(" failed p.returncode= " + str(proc.returncode))
        return proc.returncode
    
    except Exception as inst:
        print("command failed")
        print(inst)
        return -1
    

    

def main():
    git_rep , ids,  commit = pars_input(sys.argv[1])
    print ("your git repository is: " + git_rep)
    print ("your ids are: " + ids)
    print ("your commit is: " + commit)

    print("cloning your git: " + git_rep)
    run_cmd("git clone " + git_rep )

    try:
        match = re.search(r'([\w-]+)\.git', git_rep)
        dir = match.group(1)
        print("changing folder to: " + dir)
        os.chdir(dir)
    except Exception as inst:
        print("go into you git dir failed")
        print(inst)
        exit(1)
    
    print("checking out you commit: " + commit)
    run_cmd("git checkout " + commit)
        

    run_cmd("bash grade",verbos=1)
    


if __name__ == "__main__":
    main()