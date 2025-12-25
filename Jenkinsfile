pipeline {
    agent any

    environment {
        ALLURE_RESULTS = 'allure-results'
        ALLURE_REPORT = 'allure-report'
        BUILD_DIR = 'build'
    }

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Configure') {
            steps {
                script {
                    sh '''
                        mkdir -p ${BUILD_DIR}
                        cd ${BUILD_DIR}
                        cmake .. -DCMAKE_BUILD_TYPE=Release
                    '''
                }
            }
        }

        stage('Build') {
            steps {
                script {
                    sh '''
                        cd ${BUILD_DIR}
                        cmake --build . --config Release
                    '''
                }
            }
        }

        stage('Test') {
            steps {
                script {
                    sh '''
                        cd ${BUILD_DIR}
                        # Run tests and generate Allure results
                        # Allure results are generated in allure-results directory by the test executable
                        ./bin/DemoAllureProjectTests --gtest_output=xml:test-results.xml || true
                        
                        # Ensure allure-results directory exists
                        if [ ! -d "allure-results" ]; then
                            mkdir -p allure-results
                        fi
                        
                        # Copy results to project root if needed
                        if [ -d "allure-results" ] && [ "$(ls -A allure-results)" ]; then
                            echo "Allure results found: $(ls -la allure-results | head -5)"
                        else
                            echo "Warning: No Allure results generated"
                        fi
                    '''
                }
            }
        }
    }

    post {
        always {
            script {
                // Publish Allure report
                // Try build directory first, then project root
                def resultsPath = fileExists("${BUILD_DIR}/allure-results") ? 
                    "${BUILD_DIR}/allure-results" : 
                    (fileExists('allure-results') ? 'allure-results' : "${BUILD_DIR}/allure-results")
                
                allure([
                    includeProperties: false,
                    jdk: '',
                    properties: [],
                    reportBuildPolicy: 'ALWAYS',
                    results: [[path: resultsPath]]
                ])
            }
        }
        success {
            echo 'Pipeline succeeded!'
        }
        failure {
            echo 'Pipeline failed!'
        }
    }
}
