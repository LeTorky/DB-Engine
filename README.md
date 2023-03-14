<h1>Database Implementation</h1>
<p style="font-size:20px;">
    Implementing a <u>Database-Engine</u> using <u>C</u> programming language.
</p>
<h2>
    <u>Content</u>
</h2>
<ol>
    <li>
        <h4>
            <u>REPL</u>
        </h4>
        <p>
            A Read Evaluate Print Loop "REPL" which is an interface to the Database that accepts users query statements / internal commands.
        </p>
        <ul>
            <li>
                A dynamic array that stores user characters; until array is about to over-flow then it allocates extra space to store new input.
            </li>
            <li>
                With each key stroke, the REPL prints out the character then starts storing into the dynamic array.
            </li>
            <li>
                Left and Right keys move the terminal's cursor and increases / decreases the current index of the character to be inserted within the dynamic array.
            </li>
            <li>
                Backspace key removes character at index prior to current index (Where the cursor is standing at) and starts shifting the rest of the string (Characters after deleted character) to start from the said character's index.
            </li>
            <li>
                Enter key returns the address of the dynamic array to the main program to start processing the extracted user input.
            </li>
        </ul>
    </li>
</ol>