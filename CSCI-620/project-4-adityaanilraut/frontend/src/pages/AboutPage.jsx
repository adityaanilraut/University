import React, { useState, useEffect } from 'react';
import { contentApi } from '../services/api';
import './ContentPages.css';

const AboutPage = () => {
  const [about, setAbout] = useState(null);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    const fetchAbout = async () => {
      try {
        const data = await contentApi.getAbout();
        setAbout(data);
      } catch (err) {
        // Use default about if API fails
        setAbout(getDefaultAbout());
      } finally {
        setLoading(false);
      }
    };

    fetchAbout();
  }, []);

  if (loading) {
    return (
      <div className="loading-container">
        <div className="loading-spinner"></div>
        <p>Loading...</p>
      </div>
    );
  }

  return (
    <div className="page-container content-page">
      <h1 className="page-title">About</h1>
      
      {/* About Me Section */}
      <div className="about-me-section">
        <div className="about-me-content">
          <div className="about-me-image">
            <img src="/static/images/profile.jpg" alt="Aditya" />
          </div>
          <div className="about-me-text">
            <h2 className="about-me-title">About Me</h2>
            <p>
              Hello! I'm Aditya, a computer science student passionate about web development and software engineering. I enjoy exploring new technologies and building interactive applications that solve real-world problems.
            </p>
            <p>
              My interests include full-stack development, data structures and algorithms, and user interface design. I'm excited to continue learning and growing in the field of computer science, with goals of becoming a skilled software engineer and contributing to innovative projects that make a positive impact.
            </p>
          </div>
        </div>
      </div>

      <div className="about-hero">
        <div className="hero-icon">♔</div>
        <h2 className="hero-title">{about?.description}</h2>
        <p className="hero-subtitle">A modern, real-time multiplayer chess experience</p>
      </div>

      <div className="about-grid">
        {/* Features */}
        <div className="card about-card">
          <div className="card-header">
            <span className="section-icon">✨</span>
            Features
          </div>
          <ul className="feature-list">
            {about?.features?.map((feature, index) => (
              <li key={index} className="feature-item">
                <span className="feature-check">✓</span>
                {feature}
              </li>
            ))}
          </ul>
        </div>

        {/* Technologies */}
        <div className="card about-card">
          <div className="card-header">
            <span className="section-icon">🛠️</span>
            Technologies
          </div>
          
          <div className="tech-section">
            <h4 className="tech-category">Backend</h4>
            <div className="tech-tags">
              {about?.technologies?.backend?.map((tech, index) => (
                <span key={index} className="tech-tag backend">{tech}</span>
              ))}
            </div>
          </div>

          <div className="tech-section">
            <h4 className="tech-category">Frontend</h4>
            <div className="tech-tags">
              {about?.technologies?.frontend?.map((tech, index) => (
                <span key={index} className="tech-tag frontend">{tech}</span>
              ))}
            </div>
          </div>

          <div className="tech-section">
            <h4 className="tech-category">Deployment</h4>
            <div className="tech-tags">
              {about?.technologies?.deployment?.map((tech, index) => (
                <span key={index} className="tech-tag deployment">{tech}</span>
              ))}
            </div>
          </div>
        </div>
      </div>

      {/* Architecture Overview */}
      <div className="card architecture-card">
        <div className="card-header">
          <span className="section-icon">🏗️</span>
          Architecture Overview
        </div>
        <div className="architecture-diagram">
          <div className="arch-layer client">
            <span className="layer-label">Client</span>
            <div className="layer-items">
              <span>React SPA</span>
              <span>WebSocket Client</span>
            </div>
          </div>
          <div className="arch-arrow">↕</div>
          <div className="arch-layer server">
            <span className="layer-label">Server</span>
            <div className="layer-items">
              <span>Django REST API</span>
              <span>Django Channels</span>
            </div>
          </div>
          <div className="arch-arrow">↕</div>
          <div className="arch-layer data">
            <span className="layer-label">Data</span>
            <div className="layer-items">
              <span>SQLite Database</span>
              <span>python-chess Engine</span>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};

const getDefaultAbout = () => ({
  title: 'About This Project',
  description: 'CSCI 620: Real-Time Multiplayer Chess Game',
  features: [
    'Real-time multiplayer gameplay using WebSockets',
    'User authentication and registration',
    'Challenge system for starting games',
    'Game history tracking',
    'Move validation using python-chess library'
  ],
  technologies: {
    backend: ['Django', 'Django REST Framework', 'Django Channels', 'python-chess'],
    frontend: ['React', 'React Router', 'WebSocket API'],
    deployment: ['Docker', 'Google Cloud Platform']
  }
});

export default AboutPage;

