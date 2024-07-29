import React, { useState, useContext } from 'react'
import '../css/Auth.css'
import ApiClient from '../service/ApiClient';
import userContext from '../PageInfo';
import { useNavigate } from "react-router-dom";


const apiClient=new ApiClient();

const Register = () => {
    const navigate = useNavigate();
    const{setLogged, setUserId, setRole, setUserLogin} = useContext(userContext);
    const [ success, setSuccess] = useState(false);
    const [ login, setLogin ] = useState('');
    const [ name, setName ] = useState('');
    const [ surname, setSurname ] = useState('');
    const [ errorInfo, setErrorInfo ] = useState('');

    const [email, setEmail] = useState('');
    const [ emailIncorrect, setEmailIncorrect ] = useState(false);

    const [ password, setPassword ] = useState('');
    const [ passwordIncorrect, setPasswordIncorrect ] = useState(false);
    

    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    const passwordRegex = /^(?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[!@#$%^&*()_+])(?=.*[a-zA-Z]).{8,}$/;

    const handleEmailChange = (event) =>{
        setEmail(event.target.value);
        setEmailIncorrect(false);

        if(!emailRegex.test(event.target.value) && event.target.value != "")
        {
            setEmailIncorrect(true);
        }
    }

    const handlePasswordChange = (event) =>{
        setPassword(event.target.value);
        setPasswordIncorrect(false);
        if(!passwordRegex.test(event.target.value) && event.target.value != "")
        {
            setPasswordIncorrect(true);
        }
    }

    const handleRegister = async () => {
        if(!(emailIncorrect || email == "" || passwordIncorrect || password =="" || login=="" || name=="" || surname=="" ))
        {
            
            const resp = await apiClient.Register( login, password, email, name, surname );

            console.log(resp);

            if(resp[0])
            {
                const user ={
                    logged:true,
                    id:resp[2],
                    role:"CLIENT",
                    userLogin:resp[3]
                }
                const userJSON = JSON.stringify(user);
                localStorage.setItem('user',userJSON);
                setSuccess(true);
                setErrorInfo("Success registration");
                setLogged(true);
                setUserId(resp[2]);
                setRole(resp[1]);
                setUserLogin(resp[3]);
                if (resp[1] == "REPAIRER")
                    navigate(`/mechanicsServices/`);
                else
                    navigate(`/`);
            }
            else
            {
                setErrorInfo(resp[1]);
                setSuccess(false);
            }
        }
    }

    return (
        <div id ="RegisterForm">
            <h3>Email</h3>
            <input 
                name="Email" 
                placeholder="Email" 
                value={email} 
                onChange={handleEmailChange} 
                style={{
                    borderWidth: emailIncorrect ? '3px' : '1px',
                    borderColor: emailIncorrect ? 'red':''}}/>
            <h3>Login</h3>
            <input 
                name="Login" 
                placeholder="Login"
                onChange={(e) => setLogin(e.target.value)}
                />
            <h3>Password</h3>
            <input 
                name="password" 
                placeholder="Password"
                value={password} 
                type='password'
                onChange={handlePasswordChange} 
                style={{
                    borderWidth: passwordIncorrect ? '3px' : '1px',
                    borderColor: passwordIncorrect ? 'red':''}}/>
            <h3>Name</h3>
            <input 
                name="Name" 
                placeholder="Name"
                onChange={(e) => setName(e.target.value)}/>
            <h3>Surname</h3>
            <input 
                name="Surname" 
                placeholder="Surname"
                onChange={(e) => setSurname(e.target.value)}/>
            <h3 id="errorInfo" style={{
                color: success ? 'green' : 'blue'
            }}>{errorInfo}</h3>
            <button 
                name = "register"
                onClick={handleRegister}
                style={{
                    backgroundColor: (emailIncorrect || email == "" || passwordIncorrect || password =="" || login=="" || name=="" || surname=="" ) ? 'grey' : 'green'}}
                    >Register</button>
        </div>
    )
}

export default Register
