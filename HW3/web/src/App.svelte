<script>
import Init from "./Init.svelte";
	
let state = 0;
	
</script>

<main>
	<div id="title">縱痕殺棋</div>
	<Init />
	
	<!-- <textarea id="data" type="text" placeholder="請輸入棋盤資料" cols="40" rows="5"></textarea> -->
	
	
	

</main>

<style>
	#title {
		text-align: center;
		text-transform: uppercase;
		font-size: 5em;
		font-weight: 100;
		letter-spacing: 0.5em;
		font-family: 'Impact';
		color: black;
		margin: 50px;
	}

	/* #data {
		padding: 1em;
		margin: 0 auto;

		width: 500px;
		height: 500px;
		
		display: flex;
   		justify-content: center; 
		align-items: center; 
		text-align: center
		
		
		
		border-radius: 10px;

	} */
	
</style>