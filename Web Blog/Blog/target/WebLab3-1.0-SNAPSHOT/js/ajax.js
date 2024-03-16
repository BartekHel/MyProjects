/**
 * All js methods used in the project.
 * @author Bartosz Helinski
 * @version 2.0
 */

/**
 * Performs a search operation based on the provided argument and displays the result.
 * @param {string} arg1 - The ID of the input element containing the search argument.
 * @param {string} result - The ID of the element where the search result will be displayed.
 */

function getResult(arg1, result) {
    var argElement = document.getElementById(arg1);
    var resultElement = document.getElementById(result);

    var argValue = argElement.value.trim();
    if (argValue === '' || /^\s*$/.test(argValue) || /^\d+$/.test(argValue)) {
        resultElement.innerHTML = 'Blad: Podaj nazwe posta!';
        return;
    }

    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function () {
        if (this.readyState === 4 && this.status === 200) {
            document.getElementById(result).innerHTML = this.responseText;
        }
    };

    var arg = document.getElementById(arg1).value;

    xhttp.open("POST", "simplesearch?arg1=" + arg, true);
    xhttp.send();
}

/**
 * Adds a new post with the given title and content, and displays the result.
 * @param {string} arg1 - The ID of the input element containing the post title.
 * @param {string} arg2 - The ID of the input element containing the post content.
 * @param {string} result - The ID of the element where the result will be displayed.
 */

function getPostAdd(arg1, arg2, result) {
    var argElement1 = document.getElementById(arg1);
    var argElement2 = document.getElementById(arg2);
    var resultElement = document.getElementById(result);

    var argValue1 = argElement1.value.trim();
    var argValue2 = argElement2.value.trim();
    if ((argValue1 === '' || /^\s*$/.test(argValue1) || /^\d+$/.test(argValue1)) && (argValue2 === '' || /^\s*$/.test(argValue2) || /^\d+$/.test(argValue2))) {
        resultElement.innerHTML = 'Blad: Niepoprawny post!';
        return;
    }
    else if (argValue1 === '' || /^\s*$/.test(argValue1) || /^\d+$/.test(argValue1)) {
        resultElement.innerHTML = 'Blad: Niepoprawny tytul posta!';
        return;
    }
    else if (argValue2 === '' || /^\s*$/.test(argValue2) || /^\d+$/.test(argValue2)) {
        resultElement.innerHTML = 'Blad: Niepoprawna tresc posta!';
        return;
    }
    
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function () {
        if (this.readyState === 4 && this.status === 200) {
            document.getElementById(result).innerHTML = this.responseText;
        }
    };

    var ar1 = document.getElementById(arg1).value;
    var ar2 = document.getElementById(arg2).value;

    xhttp.open("POST", "addpost?arg1=" + ar1 + "&arg2=" + ar2, true);
    xhttp.send();
}

/**
 * Deletes a post based on the provided post number and displays the result.
 * @param {string} arg1 - The ID of the input element containing the post number to be deleted.
 * @param {string} result - The ID of the element where the result will be displayed.
 */

function getPostDel(arg1, result) {
    var argElement = document.getElementById(arg1);
    var resultElement = document.getElementById(result);

    var argValue = argElement.value.trim();
    if (argValue === '' || isNaN(argValue)) {
        resultElement.innerHTML = 'Blad: Podaj numer posta!';
        return;
    } else if (parseInt(argValue) <= 0 || parseInt(argValue) > 100) {
        resultElement.innerHTML = 'Blad: Nieprawidlowy numer!';
        return;
    }

    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function () {
        if (this.readyState === 4 && this.status === 200) {
            resultElement.innerHTML = this.responseText;
        }
    };

    var arg = argElement.value;

    xhttp.open("GET", "deleteposts?arg1=" + arg, true);
    xhttp.send();
}

/**
 * Retrieves the history of posts and displays the result.
 * @param {string} result - The ID of the element where the history will be displayed.
 */

function getHistory(result) {
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function () {
        if (this.readyState === 4 && this.status === 200) {
            document.getElementById(result).innerHTML = this.responseText;
        }
    };
    
    xhttp.open("GET", "history", true);
    xhttp.send();
}

/**
 * Retrieves the data base of posts and logs and displays if any erros occured.
 * @param {string} result - The ID of the element where the errors will be displayed.
 */

function getBased(result) {
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function () {
        if (this.readyState === 4 && this.status === 200) {
            document.getElementById(result).innerHTML = this.responseText;
        }
    };

    xhttp.open("GET", "database", true);
    xhttp.send();
}