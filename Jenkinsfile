pipeline {
    agent any

    environment {
        BUILD_DIR = 'build'
        TEST_RESULTS_DIR = 'test-results'
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
                        mkdir -p ${TEST_RESULTS_DIR}
                        
                        # Run tests and generate XML output
                        ./bin/DemoAllureProjectTests --gtest_output=xml:${TEST_RESULTS_DIR}/test-results.xml || true
                        
                        # Verify XML file was created
                        if [ -f "${TEST_RESULTS_DIR}/test-results.xml" ]; then
                            echo "Test results XML generated: ${TEST_RESULTS_DIR}/test-results.xml"
                            echo "File size: $(wc -l < ${TEST_RESULTS_DIR}/test-results.xml) lines"
                        else
                            echo "Warning: Test results XML not found"
                        fi
                    '''
                }
            }
        }
    }

    post {
        // always {
        //     // Publish test results
        //     junit testResultsPattern: "${BUILD_DIR}/${TEST_RESULTS_DIR}/test-results.xml", allowEmptyResults: true
        // }
        success {
            echo 'Pipeline succeeded!'
        }
        failure {
            echo 'Pipeline failed!'
        }
    }
}
