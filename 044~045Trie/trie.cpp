/*1、类描述实现前缀树
*/
  class Node1 {
     int pass;
     int end;
     Node1[] nexts;

     Node1() {
        pass = 0;
        end = 0;
        // 0    a
        // 1    b
        // 2    c
        // ..   ..
        // 25   z
        // nexts[i] == null   i方向的路不存在
        // nexts[i] != null   i方向的路存在
        nexts = new Node1[26];
    }
}

  class Trie1 {
    private Node1 root;

     Trie1() {
        root = new Node1();
    }

     void insert(String word) {
        if (word == null) {
            return;
        }
        char[] str = word.toCharArray();
        Node1 node = root;
        node.pass++;
        int path = 0;
        for (int i = 0; i < str.length; i++) { // 从左往右遍历字符
            path = str[i] - 'a'; // 由字符，对应成走向哪条路
            if (node.nexts[path] == null) {
                node.nexts[path] = new Node1();
            }
            node = node.nexts[path];
            node.pass++;
        }
        node.end++;
    }

     void delete(String word) {
        if (search(word) != 0) {
            char[] chs = word.toCharArray();
            Node1 node = root;
            node.pass--;
            int path = 0;
            for (int i = 0; i < chs.length; i++) {
                path = chs[i] - 'a';
                if (--node.nexts[path].pass == 0) {
                    node.nexts[path] = null;
                    return;
                }
                node = node.nexts[path];
            }
            node.end--;
        }
    }

    // word这个单词之前加入过几次
     int search(String word) {
        if (word == null) {
            return 0;
        }
        char[] chs = word.toCharArray();
        Node1 node = root;
        int index = 0;
        for (int i = 0; i < chs.length; i++) {
            index = chs[i] - 'a';
            if (node.nexts[index] == null) {
                return 0;
            }
            node = node.nexts[index];
        }
        return node.end;
    }

    // 所有加入的字符串中，有几个是以pre这个字符串作为前缀的
     int prefixNumber(String pre) {
        if (pre == null) {
            return 0;
        }
        char[] chs = pre.toCharArray();
        Node1 node = root;
        int index = 0;
        for (int i = 0; i < chs.length; i++) {
            index = chs[i] - 'a';
            if (node.nexts[index] == null) {
                return 0;
            }
            node = node.nexts[index];
        }
        return node.pass;
    }
}




/*2、固定数组实现前缀树
*/
{
 int MAXN=150001;
 int [][] tree[MAXN][26];
 int [] pass[MAXN];
 int [] end[MAXN];
    void bulid(){
    cnt=1;
}

void insert(String word) {
        if (word == null) {
            return;
        }
        int path = 0;
        int cur=1;
        pass[cnt]++;
        for (int i = 0; i < word.length; i++) { // 从左往右遍历字符
            path = word[i] - 'a'; // 由字符，对应成走向哪条路
            if (tree[cur][path]==0) {
                tree[cur][path]=cnt++;
            }
            cur=tree[cur][path];
            pass[cur]++;
        }
        end[cur]++;
    }

    void delete(String word) {
        if (search(word) != 0) {
            int cur=1;
            int path = 0;
            for (int i = 0; i < word.length; i++) {
                path = word[i] - 'a';
                if (--pass[tree[cur][path]] == 0) {
                    tree[cur][path]=0;
                    return;
                }
                cur=tree[cur][path];
            }
            end[cur]--;
        }
    }

    // word这个单词之前加入过几次
    int search(String word) {
        if (word == null) {
            return 0;
        }
        int cur=1;
        int index=0;
        for (int i = 0; i < word.length; i++) {
            index = word[i] - 'a';
            if (tree[cur][index] == 0) {
                return 0;
            }
            cur=tree[cur][index];
        }
        return end[cur];
    }

    // 所有加入的字符串中，有几个是以pre这个字符串作为前缀的
    int prefixNumber(String pre) {
        if (pre == null) {
            return 0;
        }
        int cur=1;
        int index = 0;
        for (int i = 0; i < word.length; i++) {
            index = word[i] - 'a';
            if (tree[cur][index] == 0) {
                return 0;
            }
            cur=tree[cur][index];
        }
        return pass[cur];
    }
}

/*3、哈希表实现前缀树
*/
 class Node2 {
     int pass;
     int end;
     HashMap<Integer, Node2> nexts;

     Node2() {
        pass = 0;
        end = 0;
        nexts = new HashMap<>();
    }
}

  class Trie2 {
    private Node2 root;

     Trie2() {
        root = new Node2();
    }

     void insert(String word) {
        if (word == null) {
            return;
        }
        char[] chs = word.toCharArray();
        Node2 node = root;
        node.pass++;
        int index = 0;
        for (int i = 0; i < chs.length; i++) {
            index = (int) chs[i];
            if (!node.nexts.containsKey(index)) {
                node.nexts.put(index, new Node2());
            }
            node = node.nexts.get(index);
            node.pass++;
        }
        node.end++;
    }

     void delete(String word) {
        if (search(word) != 0) {
            char[] chs = word.toCharArray();
            Node2 node = root;
            node.pass--;
            int index = 0;
            for (int i = 0; i < chs.length; i++) {
                index = (int) chs[i];
                if (--node.nexts.get(index).pass == 0) {
                    node.nexts.remove(index);
                    return;
                }
                node = node.nexts.get(index);
            }
            node.end--;
        }
    }

    // word这个单词之前加入过几次
     int search(String word) {
        if (word == null) {
            return 0;
        }
        char[] chs = word.toCharArray();
        Node2 node = root;
        int index = 0;
        for (int i = 0; i < chs.length; i++) {
            index = (int) chs[i];
            if (!node.nexts.containsKey(index)) {
                return 0;
            }
            node = node.nexts.get(index);
        }
        return node.end;
    }

    // 所有加入的字符串中，有几个是以pre这个字符串作为前缀的
     int prefixNumber(String pre) {
        if (pre == null) {
            return 0;
        }
        char[] chs = pre.toCharArray();
        Node2 node = root;
        int index = 0;
        for (int i = 0; i < chs.length; i++) {
            index = (int) chs[i];
            if (!node.nexts.containsKey(index)) {
                return 0;
            }
            node = node.nexts.get(index);
        }
        return node.pass;
    }
}