def load(filename : str):
    keys = []
    temporary = []

    def finish_value():
        assert(len(temporary) >= 2)

        add_to = temporary[-2]

        if type(add_to) is list:
            add_to.append(temporary.pop())
        elif type(add_to) is dict:
            add_to[keys.pop()] = temporary.pop()
        else:
            assert(False)

    def process_value(view: str):
        if (view.startswith("!<ARRAY>")):
            temporary.append([])
        elif (view.startswith("!<DICT>")):
            temporary.append({})
        elif (view.startswith("!<VALUE>")):
            temporary.append(view[9:-1])
            finish_value()
        else:
            assert(False)
    
    with open(filename) as source:
        preprocessed = False
        lines = source.readlines()
        for line in lines:
            i = 0
            while line[i] == ' ':
                i += 1
            assert(i % 2 == 0)
            depth = i // 2
            assert(depth <= len(temporary))

            line_view = line[depth * 2:]
            if line_view.startswith("//"):
                continue

            while depth < len(temporary):
                finish_value()
            
            if not preprocessed:
                preprocessed = True
                process_value(line_view)
            elif type(temporary[-1]) is list:
                process_value(line_view)
            elif type(temporary[-1]) is dict:
                key_idx = line_view.find(':')
                keys.append(line_view[:key_idx])
                process_value(line_view[key_idx + 2:])
            else:
                assert(False)
        
        while len(temporary) > 1:
            finish_value()
        assert(len(temporary) == 1)
        return temporary[0]
    
def save(obj: any, filename: str):
    with open(filename, "w") as target:
        def save_impl(v, depth, key):
            prefix = " " * depth * 2
            target.write(prefix)
            if key is not None:
                target.write(key)
                target.write(": ")
            
            if type(v) is list:
                target.write("!<ARRAY>\n")
                for vs in v:
                    save_impl(vs, depth + 1, None)
            elif type(v) is dict:
                target.write("!<DICT>\n")
                for key, vs in sorted(v.items()):
                    save_impl(vs, depth + 1, key)
            elif type(v) is str:
                target.write("!<VALUE> ")
                target.write(v)
                target.write("\n")
            else:
                assert(False)
        save_impl(obj, 0, None)