import React from 'react';
import { Link, useLocation, useNavigate } from 'react-router-dom';
import { useAuth } from '../contexts/AuthContext';
import './Navigation.css';

const Navigation = () => {
  const { user, logout, isAuthenticated } = useAuth();
  const location = useLocation();
  const navigate = useNavigate();

  const handleLogout = async () => {
    await logout();
    navigate('/login');
  };

  const isActive = (path) => location.pathname === path;

  return (
    <nav className="navigation">
      <div className="nav-container">
        <Link to="/" className="nav-brand">
          <span className="brand-icon">♔</span>
          <span className="brand-text">Chess Arena</span>
        </Link>

        <div className="nav-links">
          {isAuthenticated ? (
            <>
              <Link 
                to="/lobby" 
                className={`nav-link ${isActive('/lobby') ? 'active' : ''}`}
              >
                Lobby
              </Link>
              <Link 
                to="/history" 
                className={`nav-link ${isActive('/history') ? 'active' : ''}`}
              >
                History
              </Link>
            </>
          ) : null}
          <Link 
            to="/rules" 
            className={`nav-link ${isActive('/rules') ? 'active' : ''}`}
          >
            Rules
          </Link>
          <Link 
            to="/about" 
            className={`nav-link ${isActive('/about') ? 'active' : ''}`}
          >
            About
          </Link>
        </div>

        <div className="nav-auth">
          {isAuthenticated ? (
            <>
              <span className="nav-user">
                <span className="user-icon">♟</span>
                {user?.username}
              </span>
              <button onClick={handleLogout} className="btn btn-secondary btn-sm">
                Logout
              </button>
            </>
          ) : (
            <>
              <Link to="/login" className="btn btn-secondary btn-sm">
                Login
              </Link>
              <Link to="/register" className="btn btn-primary btn-sm">
                Register
              </Link>
            </>
          )}
        </div>
      </div>
    </nav>
  );
};

export default Navigation;

