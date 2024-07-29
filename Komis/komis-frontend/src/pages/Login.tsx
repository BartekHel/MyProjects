import React, { useContext, useState } from 'react'
import '../css/Auth.css'
import ApiClient from '../service/ApiClient'
import userContext from '../PageInfo';
import { useNavigate } from "react-router-dom";

const apiClient = new ApiClient();

const Login = () => {
    const navigate = useNavigate();
    const [ success, setSuccess] = useState(false);
    const [ login, setLogin ] = useState('');
    const [ password, setPassword ] = useState('');
    const [ errorInfo, setErrorInfo ] = useState('');
    const{setLogged, setUserId, setRole, setUserLogin} = useContext(userContext);

    const handleLogin = async() => {
        if(!(password =="" || login==""))
        {
            const resp = await apiClient.Login( login, password)
            console.log(resp)
            if(resp[0])
            {
                const user ={
                    logged:true,
                    id:resp[2],
                    role:resp[1], 
                    userLogin:resp[3]
                }
                const userJSON = JSON.stringify(user);
                localStorage.setItem('user',userJSON);
                setErrorInfo("Success login");
                setSuccess(true);
                setLogged(true);
                setUserLogin(resp[3]);
                setUserId(resp[2]);
                setRole(resp[1]);
                if (resp[1] == "REPAIRER")
                    navigate(`/mechanicsServices/`);
                else
                    navigate(`/`);
            }
            else
            {
                setErrorInfo("Incorrect login or password");
                setSuccess(false);
            }
            
        }
    }

    return (
        <div id ="RegisterForm">
            
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
                onChange={(e) => setPassword(e.target.value)}/>
            
            <h3 id="errorInfo" style={{
                color: success ? 'green' : 'blue'
            }}>{errorInfo}</h3>

            
            <button 
                name = "login"
                onClick={handleLogin}
                style={{
                    backgroundColor: (password =="" || login=="") ? 'grey' : 'green'}}
                    >Login</button>
        </div>
    )
}

export default Login
