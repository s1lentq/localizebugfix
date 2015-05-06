#localizebugfix

Fix exploit localization strings in nickname and chat

## How it works?

<ol>
<li>
The chat must be modified with using client_print_color/client_print where the player will write in the chat message
The content of the message:
<pre>
	s1lent :#Spec_Help_Text Hello people! #Spec_Duck
</pre>
every the client if received message - the client will get crash
</li>
<li>
Using with the message ShowMenu
<pre>
	name "q#Buy#Buy#Buy#Buy#Buy#Buy#Buy"
</pre>
The client to after open the menu with list of players - the client will get crash
</li>
</ol>
