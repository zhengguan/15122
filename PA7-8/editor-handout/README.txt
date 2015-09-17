15-122 Principles of Imperative Computation
Editor

Files you won't modify:
   gapbuf-test.c0 - Test for gap buffers
   dll_pt-test.c0 - Test for doubly-linked lists with a point
   tbuf-test.c0   - Test for text buffers
   lovas-E0.c0    - The E0 text editor implementation

Files you will modify:
   gapbuf.c0 - Gap buffers
      bool is_gapbuf(struct gapbuf_header* G);
      bool gapbuf_empty(gapbuf G);    /* Returns true if the buffer is empty */
      bool gapbuf_full(gapbuf G);     /* Returns true if the buffer is full  */
      bool gapbuf_at_left(gapbuf G);  /* Returns true if the gap is at the   */
                                      /*   left end of the buffer            */
      bool gapbuf_at_right(gapbuf G); /* Returns true if the gap is at the   */
                                      /*   right end of the buffer           */
      gapbuf gapbuf_new(int limit);   /* Create a new gapbuf of size limit   */
      void gapbuf_forward(gapbuf G);  /* Move the gap forward, to the right  */
      void gapbuf_backward(gapbuf G); /* Move the gap backward, to the left  */
      void gapbuf_insert(gapbuf G, char c); /* Insert char c before the gap  */
      void gapbuf_delete(gapbuf G);   /* Delete the char before the gap      */

   dll_pt.c0 - Doubly-linked lists with a point
      bool is_dll_pt(struct dll_pt_header* B);
      bool dll_pt_at_left(dll_pt B);  /* Returns true if the point is first  */
                                      /*   first (non-terminal) node         */
      bool dll_pt_at_right(dll_pt B); /* Returns true if the point is last   */
                                      /*   last (non-terminal) node          */
      void dll_pt_forward(dll_pt B);  /* Moves the point forward (right)     */
      void dll_pt_backward(dll_pt B); /* Moves the point backward (left)     */
      void dll_pt_delete(dll_pt B);   /* Remove the current point            */

   tbuf.c0 - Text buffers
      bool is_tbuf(struct dll_pt_header* B);
      tbuf tbuf_new();                /* Creates an empty text buffer        */
      void tbuf_split_pt(tbuf B);     /* Splits a full point into two nodes  */
      void tbuf_forward(tbuf B);      /* Move the cursor forward/right by 1  */
      void tbuf_backward(tbuf B);     /* Move the cursor backward/left by 1  */
      void tbuf_insert(tbuf B, char c); /* Insert the char before the cursor */
      void tbuf_delete(tbuf B);       /* Delete the char before the cursor   */

==========================================================

Compiling and running the gapbuf tests:
   % cc0 -d -w -o gapbuf-test gapbuf.c0 gapbuf-test.c0
   % ./gapbuf-test 16
   Visualizing the 16-element gap-buffer.
   Give initial input (empty line quits):
   space race<<<<<<<<^p<<the >>^p>>>>>>>>!!<<<<<<<^^^^^great
        [................]
   's': s[...............]
   'p': sp[..............]
   'a': spa[.............]
   ...

Compiling and running the dll_pt tests:
   % cc0 -d -w -o dll_pt-test elem-char.c0 dll_pt.c0 dll_pt-test.c0
   % ./dll_pt-test
   Visualizing the text buffer with elem as char.
   Give an initial input for the buffer (empty line quits): foo
   Initial buffer: START <--> 'f' <--> 'o' <--> _'o'_ <--> END
   Give actions (empty line quits): <^^
        START <--> 'f' <--> 'o' <--> _'o'_ <--> END
   <= : START <--> 'f' <--> _'o'_ <--> 'o' <--> END
   del: START <--> 'f' <--> _'o'_ <--> END
   del: START <--> _'f'_ <--> END
   ...

Compiling and running the tbuf tests:
   % cc0 -d -w -o tbuf-test gapbuf.c0 dll_pt.c0 tbuf.c0 tbuf-test.c0
   % ./tbuf-test
   Visualizing text buffers: doubly linked lists of 16-element gap buffers.
   The '<' character mimics going backwards (left arrow key)
   The '>' character mimics going forwards (right arrow key)
   The '^' character mimics deletion (delete key)
   All other characters just insert that character

   Give initial input (empty line quits):
   abc<^^^<>>^^abcdefghABCDEFGH><<<<<<<<<<<<<<<<<<<<>>>12345678#WXYZ<<<<wxyz#
   START <--> _[................]_ <--> END
   'a': START <--> _a[...............]_ <--> END
   ...
   Done. More input? (empty line quits):
   ^^^^^^^^^^>^^^^^^^^^>>>>>>>>>>>>>>>>>>>^^^^^^^^^^^^^^^^^
   ...

Compiling and running the E0 editor:
   % cc0 -d -w -o E0 gapbuf.c0 dll_pt.c0 tbuf.c0 lovas-E0.c0
   % ./E0

==========================================================

Submitting with Andrew handin script (CHECKPOINT):
   % handin editor-check gapbuf.c0

Submitting with Andrew handin script (FINAL):
   % handin editor-final gapbuf.c0 dll_pt.c0 tbuf.c0

Creating a tarball to submit with Autolab web interface:
   % tar -czvf edhandin.tgz gapbuf.c0 dll_pt.c0 tbuf.c0

On autolab (checkpoint): https://autolab.cs.cmu.edu/15122-f14/editorcheck
On autolab (final): https://autolab.cs.cmu.edu/15122-f14/editor
