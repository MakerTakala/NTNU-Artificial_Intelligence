<script>

let state = 0;

</script>

<div id="init">
    <button class="initbutton" id="manualdata" value="點選輸入" on:click="{() => state = 1}" ></button>
    <button class="initbutton" id="textdata "value="文字輸入" on:click="{() => state = 2}"></button>
</div>


<style>

#init {
    width: 100%;
    height: 30%;
    align-items: center;
    display: flex;
    justify-content: center;    
    align-items: center;        
}

.initbutton {
    margin: 30px;
    width: 150px;
    height: 70px;
    display: flex;
    justify-content: center;    
    align-items: center;
    text-align: center;
    border-radius: 10px;
    border-width: 3px;
}


</style>